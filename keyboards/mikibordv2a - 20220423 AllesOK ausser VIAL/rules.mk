# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
VIA_ENABLE			= yes
LTO_ENABLE 			= yes
BOOTMAGIC_ENABLE 	= yes		# Virtual DIP switch configuration
MOUSEKEY_ENABLE 	= yes       # no ORIG  Mouse keys
EXTRAKEY_ENABLE 	= yes		# Audio control and System control
CONSOLE_ENABLE 		= no		# Console for debug
COMMAND_ENABLE		= no		# Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE	= no       	# Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE 		= yes		# USB Nkey Rollover
BACKLIGHT_ENABLE 	= no		# Enable keyboard backlight functionality
BLUETOOTH_ENABLE 	= no		# Enable Bluetooth
AUDIO_ENABLE 		= no        # Audio output
ENCODER_ENABLE 		= yes
RGBLIGHT_ENABLE 	= yes
RGB_DI_PIN 			= D3		# LED Dout PinNo.
RGBLED_NUM 			= 16		# LED Anzahl

