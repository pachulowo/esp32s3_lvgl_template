#include "scr_splash.h"
#include "screens.h"
#include "ui.h"             /* access Squareline widget objects (e.g. ui_lblTitle) */
#include "esp_log.h"

static const char *TAG = "scr_splash";

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

void scr_splash_prepare(void)
{
    /* Register callbacks on widgets that must stay active across screens.
     * Example:
     *   lv_obj_add_event_cb(ui_btnSettings, on_btn_pressed, LV_EVENT_CLICKED, NULL);
     */
    ESP_LOGD(TAG, "prepare");
}

void scr_splash_init(void)
{
    /* Called every time the main screen becomes active.
     * Refresh dynamic content, restart animations, etc.
     * Example:
     *   lv_label_set_text(ui_lblStatus, "Ready");
     */
    ESP_LOGD(TAG, "init");
}

void scr_splash_uninit(void)
{
    /* Called when leaving the main screen.
     * Stop any screen-local timers or animations here.
     */
    ESP_LOGD(TAG, "uninit");
}

void scr_splash_step(void)
{
    /* Called every ~20 ms while the main screen is active.
     * Poll sensors, update progress bars, handle encoder deltas, etc.
     * Keep this function fast — avoid blocking calls.
     */
}















// /* scr_settings.c */
// #include "scr_splash.h"
// #include "screens.h"
// #include "ui.h"   /* acceso a ui_scrSettings, ui_lblTitulo, etc. */
// #include "esp_log.h"

// static const char *TAG = "scr_splash";

// void scr_splash_prepare(void)
// {
//     /* Registra callbacks persistentes en widgets que sobreviven entre pantallas.
//      * Ejemplo:
//      *   lv_obj_add_event_cb(ui_btnVolver, on_volver_cb, LV_EVENT_CLICKED, NULL);
//      */
// }

// void scr_splash_init(void)
// {
//     /* Refresca contenido dinámico al entrar en la pantalla.
//      * Ejemplo:
//      *   lv_slider_set_value(ui_sliderBrillo, brillo_actual, LV_ANIM_OFF);
//      */
//     ESP_LOGD(TAG, "init");
// }

// void scr_splash_uninit(void)
// {
//     /* Detén animaciones o timers locales al salir. */
//     ESP_LOGD(TAG, "uninit");
// }

// void scr_splash_step(void)
// {
//     /* Lógica cada ~20 ms. Evita bloqueos. */
// }