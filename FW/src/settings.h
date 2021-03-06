#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <stdint.h>
#include <nvs.h>

#ifndef SETTINGS_DELAY_SAVE
	#define SETTINGS_DELAY_SAVE		5000
#endif

typedef	struct 
{
	double Kp;
	double Ki;
	double Kd;
	double setpoint;
} pidsettings_t;

typedef struct
{
	pidsettings_t pid1;
	pidsettings_t pid2;
} settings_t;

class SettingsManager
{
	public:
		bool begin();
		void loop();
		void saveDelayed(time_t when = SETTINGS_DELAY_SAVE);
		void setDefaults();

		settings_t settings;
		
	private:
		bool write_flash();
		bool read_flash();
		bool initialize_flash();
		bool erase();

		esp_err_t _err = ESP_OK;
		bool _init = false;
		nvs_handle _handle = 0;
		time_t _saveat = 0;
		bool _dirty = true;
};

#endif //__SETTINGS_H

