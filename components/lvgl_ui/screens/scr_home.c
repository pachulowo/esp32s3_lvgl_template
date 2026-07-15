#include "scr_home.h"
#include "screens.h"
#include "ui.h"             /* access Squareline widget objects (e.g. ui_lblTitle) */
#include "esp_log.h"
#include "bsp_battery.h"
#include "esp_timer.h"
#include "driver/temperature_sensor.h"


static const char *TAG = "scr_home";

/* ------------------------------------------------------------------ */
/* Persistent event callbacks — registered in prepare(), survive screen
 * transitions because they are attached to the widget, not the screen. */
/* ------------------------------------------------------------------ */

/* Example:
static void on_btn_pressed(lv_event_t *e)
{
    (void)e;
    ui_screens_navigate(SCREEN_SETTINGS);
}
*/

/* ------------------------------------------------------------------ */

void scr_home_prepare(void)
{
    /* Register callbacks on widgets that must stay active across screens.
     * Example:
     *   lv_obj_add_event_cb(ui_btnSettings, on_btn_pressed, LV_EVENT_CLICKED, NULL);
     */
    ESP_LOGD(TAG, "prepare");
}
temperature_sensor_handle_t temp_handle;
void scr_home_init(void)
{
    /* Called every time the main screen becomes active.
     * Refresh dynamic content, restart animations, etc.
     * Example:
     *   lv_label_set_text(ui_lblStatus, "Ready");
     */
    ESP_LOGD(TAG, "init");

    temp_handle = NULL;
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(20, 50);
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor_config, &temp_handle));
    temperature_sensor_enable(temp_handle);

    bsp_battery_init();
}

void scr_home_uninit(void)
{
    /* Called when leaving the main screen.
     * Stop any screen-local timers or animations here.
     */
    ESP_LOGD(TAG, "uninit");
}

void scr_home_step(void)
{
    /* Called every ~20 ms while the main screen is active.
     * Poll sensors, update progress bars, handle encoder deltas, etc.
     * Keep this function fast — avoid blocking calls.
     */
    
    #pragma region tiempo
    int64_t tiempo = esp_timer_get_time();

    uint32_t segundos = tiempo / 1000000;

    uint32_t horas = segundos / 3600;
    uint32_t minutos = (segundos % 3600) / 60;
    uint32_t seg = segundos % 60;

    char texto[20];
    sprintf(texto, "%02lu:%02lu:%02lu", horas, minutos, seg);
    lv_label_set_text(ui_Tiempo,texto);
    #pragma endregion

    #pragma region temperatura
    float tsens_out;
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_handle, &tsens_out));
    char textoC[20];
    snprintf(textoC, sizeof(textoC), "%.1f °C", tsens_out);

    lv_label_set_text(ui_Temperatura,textoC);
    #pragma endregion

    #pragma region bateria

    float voltaje;
    uint16_t adc;

    bsp_battery_get_voltage(&voltaje,&adc);

    int porcentaje = (int)((voltaje - 3.4f) * 100.0f / (4.2f - 3.4f));

    porcentaje = porcentaje > 100 ? 100 : porcentaje;
    porcentaje = porcentaje < 0 ? 0 : porcentaje;

    lv_arc_set_value(ui_Bateria, porcentaje);
    #pragma endregion 
}