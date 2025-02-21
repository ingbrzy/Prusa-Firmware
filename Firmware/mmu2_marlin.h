/// @file
/// The sole purpose of this interface is to separate Marlin1/Marlin2 from the MMU top logic layer.
/// Why?
/// - unify implementation among MK3 and Buddy FW
/// - enable unit testing of MMU top layer
#pragma once
#include <stdint.h>

namespace MMU2 {

/// @@TODO hmmm, 12 bytes... may be we can reduce that
struct pos3d {
    float xyz[3];
    pos3d() = default;
    inline constexpr pos3d(float x, float y, float z)
        : xyz { x, y, z } {}
    pos3d operator=(const float *newP) {
        for (uint8_t i = 0; i < 3; ++i) {
            xyz[i] = newP[i];
        }
        return *this;
    }
};

void extruder_move(float distance, float feed_rate);
void extruder_schedule_turning(float feed_rate);

float move_raise_z(float delta);

void planner_abort_queued_moves();
void planner_synchronize();
bool planner_any_moves();
float stepper_get_machine_position_E_mm();
float planner_get_current_position_E();
void planner_set_current_position_E(float e);
pos3d planner_current_position();

void motion_do_blocking_move_to_xy(float rx, float ry, float feedRate_mm_s);
void motion_do_blocking_move_to_z(float z, float feedRate_mm_s);

void nozzle_park();

bool marlin_printingIsActive();
void marlin_manage_heater();
void marlin_manage_inactivity(bool b);
void marlin_idle(bool b);
void marlin_refresh_print_state_in_ram();
void marlin_clear_print_state_in_ram();
void marlin_stop_and_save_print_to_ram();

int16_t thermal_degTargetHotend();
int16_t thermal_degHotend();
void thermal_setExtrudeMintemp(int16_t t);
void thermal_setTargetHotend(int16_t t);

void safe_delay_keep_alive(uint16_t t);

void Enable_E0();
void Disable_E0();

bool all_axes_homed();

void gcode_reset_stepper_timeout();

} // namespace MMU2
