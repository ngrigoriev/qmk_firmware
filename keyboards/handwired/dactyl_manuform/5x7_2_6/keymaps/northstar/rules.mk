MCU = atmega32u4

ENCODER_ENABLE = no
RGBLIGHT_ENABLE = no

AUDIO_ENABLE = no
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no

# https://docs.qmk.fm/features/caps_word#caps-word
CAPS_WORD_ENABLE = yes

# https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-execution
DEFERRED_EXEC_ENABLE = yes

# 1 - conflicts with the home row modifiers
# 2 - problematic for the tools like vim where a single wrong character can cause lots of troubles in normal mode
AUTO_SHIFT_ENABLE = yes
# and retro shift corrects this

EXTRAKEY_ENABLE = yes
# COMMAND_ENABLE = yes
MAGIC_ENABLE = yes
BOOTMAGIC_ENABLE = yes

MOUSEKEY_ENABLE = yes
