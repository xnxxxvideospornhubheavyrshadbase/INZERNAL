#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>

void menu::cheats_tab() {
    auto local = sdk::GetGameLogic()->GetLocalPlayer();
   /* if (local) {
        printf("%f %f %f\n", local->accel, local->accel_verify, local->accel - local->accel_verify * 0.5f);
        printf("%.0f %.0f %.0f %.0f\n", local->speed, local->speed_second, local->speed_verify, local->speed - local->speed_verify * 0.5f);
        float bakery = local->speed_second - ((local->speed - local->speed_verify * 0.5f) + local->speed_verify);
        float bakery2 = local->accel_second - ((local->accel - local->accel_verify * 0.5f) + local->accel_verify);
        printf("bakery: %f %f\n", bakery, bakery2);
    }*/
    if (ImGui::Button("Try shit out")) {
        //14190 28129 27879 250
        //     bakery : 0.000000

       /* float target = 350.f;
        float temp = local->speed_verify;
        local->speed_second = temp + target;
        local->speed = temp * 0.5f + target;*/

        printf("%llx\n", &local->speed_unused);
        printf("%llx\n", &local->gravity_unused);
        printf("%llx\n", &local->accel_unused);

        //if (local->speed - local->speed_verify <= 0) {

        //}
        //local->speed_second local->speed += 100.0f;
        //local->speed_verify += 200.0f;
    }
    ImGui::Text("This tab is work in progress at the moment.");
    if (ImGui::CollapsingHeader("Punch/build cooldown changer")) {
        if (ImGui::BeginChild("###cooldownchanger", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enabled###punch", &opt::cheat::punch_cooldown_on);
            ImGui::SameLine();
            ImGui::SliderFloat("####pcoold", &opt::cheat::punch_cooldown_val, 0.05f, 0.4f, "%0.2f");
            ImGui::Text("Shouldn't ban but low values will disconnect.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Gravity changer")) {
        if (ImGui::BeginChild("###gravitychanger", AUTOSIZE(2), true)) {
            ImGui::Checkbox("Enabled###grav", &opt::cheat::gravity_on);
            ImGui::SameLine();
            ImGui::SliderFloat("###grav", &opt::cheat::gravity_val, -500.0f, 2000.f, "%0.0f");
            ImGui::Text("Shouldn't ban except negative/zero gravity when in air for too long.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Movement speed changer")) {
        if (ImGui::BeginChild("###movchanger", AUTOSIZE(3), true)) {
            ImGui::Checkbox("Enabled###movtoggle", &opt::cheat::movespeed_on);
            ImGui::SameLine();
            imwrap::checkbox("Instant Stop", opt::cheat::movespeed_stop, "Removes deceleration, resulting in instant stops to movement.");
            ImGui::SameLine();
            imwrap::checkbox("Instant Accel", opt::cheat::movespeed_start, "Removes acceleration, giving you full moving speed instantly.");

            ImGui::SliderFloat("###movspeed", &opt::cheat::movespeed_val, 100.f, 1400.f, "%0.0f");
            ImGui::Text("Shouldn't ban except maybe at really high speeds or special situations.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Acceleration changer")) {
        if (ImGui::BeginChild("###accelchanger", AUTOSIZE(2), true)) {
            static bool enabled = false;
            static float accel = 1200.f;
            ImGui::Checkbox("Enabled###accel", &enabled);
            ImGui::SameLine();
            if (ImGui::SliderFloat("###accel", &accel, 100.f, 4400.f, "%0.0f") && enabled) {
                float target = accel;
                float temp = local->accel_verify;
                local->accel_second = temp + target;
                local->accel = temp * 0.5f + target;
            }
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Move speed changer 2")) {
        if (ImGui::BeginChild("###accelchanger2", AUTOSIZE(2), true)) {
            static bool enabled = false;
            static float accel = 250.f;
            ImGui::Checkbox("Enabled###accel2", &enabled);
            ImGui::SameLine();
            if (ImGui::SliderFloat("###accel2", &accel, 100.f, 1000.f, "%0.0f") && enabled) {
                float target = accel;
                float temp = local->speed_verify;
                local->speed_second = temp + target;
                local->speed = temp * 0.5f + target;
            }
            ImGui::EndChild();
        }
    }
}