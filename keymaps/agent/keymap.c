/* hifumi "agent" keymap
 * CLI AIエージェント (Claude Code / Codex CLI / opencode / pi) 共通操作用
 */
#include QMK_KEYBOARD_H

enum layers {
    BASE,
    FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        LT(FN, KC_ESC), KC_UP,   KC_ENT,
        S(KC_TAB),      KC_DOWN, LGUI(KC_H)
    ),
    [FN] = LAYOUT(
        _______,        MS_WHLU, C(KC_C),
        KC_TAB,         MS_WHLD, QK_BOOT
    )
};

#ifdef RGBLIGHT_ENABLE
/* FNレイヤー中はLEDをオレンジに、離したら元の設定へ戻す */
layer_state_t layer_state_set_user(layer_state_t state) {
    static bool saved = false;
    static uint8_t h, s, v, mode;
    if (layer_state_cmp(state, FN)) {
        if (!saved) {
            h = rgblight_get_hue(); s = rgblight_get_sat(); v = rgblight_get_val();
            mode = rgblight_get_mode();
            saved = true;
        }
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(HSV_ORANGE);
    } else if (saved) {
        rgblight_mode_noeeprom(mode);
        rgblight_sethsv_noeeprom(h, s, v);
        saved = false;
    }
    return state;
}
#endif
