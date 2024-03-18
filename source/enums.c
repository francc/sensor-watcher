// Copyright (c) 2024 José Francisco Castro <me@fran.cc>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "devices.h"
#include "enums.h"
#include "postman.h"

const char *board_model_labels[] = {
	[BOARD_MODEL_NONE]	 					"",
	[BOARD_MODEL_GENERIC_ESP32] 			"generic_esp32",
	[BOARD_MODEL_M5STACK_ATOM_LITE] 		"m5stack_atom_lite",
	[BOARD_MODEL_M5STACK_ATOM_MATRIX] 		"m5stack_atom_matrix",
	[BOARD_MODEL_M5STACK_ATOM_ECHO] 		"m5stack_atom_echo",
	[BOARD_MODEL_M5STACK_ATOM_U] 			"m5stack_atom_u",
	[BOARD_MODEL_M5STACK_ATOMS3] 			"m5stack_atoms3",
	[BOARD_MODEL_M5STACK_ATOMS3_LITE] 		"m5stack_atoms3_lite",
	[BOARD_MODEL_M5STACK_M5STICKC] 			"m5stack_m5stickc",
	[BOARD_MODEL_M5STACK_M5STICKC_PLUS] 	"m5stack_m5stickc_plus",
	[BOARD_MODEL_M5STACK_CORE2] 			"m5stack_core2",
	[BOARD_MODEL_M5STACK_CORE2_AWS] 		"m5stack_core2_aws",
	[BOARD_MODEL_M5STACK_TOUGH] 			"m5stack_tough",
	[BOARD_MODEL_M5STACK_M5STATION_BAT] 	"m5stack_m5station_bat",
	[BOARD_MODEL_M5STACK_M5STATION_485] 	"m5stack_m5station_485",
	[BOARD_MODEL_ADAFRUIT_ESP32_FEATHER_V2] "adafruit_esp32_feather_v2",
	[BOARD_MODEL_ADAFRUIT_ESP32_S3_FEATHER] "adafruit_esp32_s3_feather",
	[BOARD_MODEL_ADAFRUIT_QT_PY_ESP32_PICO] "adafruit_qt_py_esp32_pico",
	[BOARD_MODEL_ADAFRUIT_QT_PY_ESP32_S3] 	"adafruit_qt_py_esp32_s3",
	[BOARD_MODEL_SEEEDSTUDIO_XIAO_ESP32S3] 	"seeedstudio_xiao_esp32s3",
};

const char *resource_labels[] = {
	[RESOURCE_NONE]			"",
	[RESOURCE_APPLICATION]	"application",
	[RESOURCE_BOARD]		"board",
	[RESOURCE_WIFI]			"wifi",
	[RESOURCE_I2C]			"I2C",
	[RESOURCE_ONEWIRE]		"OneWire",
	[RESOURCE_BLE]			"BLE",
	[RESOURCE_ADC]			"ADC",
};

const char *backend_status_labels[] = {
	[BACKEND_STATUS_OFFLINE]	"offline",
	[BACKEND_STATUS_ONLINE]		"online",
	[BACKEND_STATUS_ERROR]		"error",
};

const char *backend_auth_labels[] = {
	[BACKEND_AUTH_NONE]		"",
	[BACKEND_AUTH_BASIC]	"basic",
	[BACKEND_AUTH_DIGEST]	"digest",
	[BACKEND_AUTH_BEARER]	"bearer",
	[BACKEND_AUTH_TOKEN]	"token",
	[BACKEND_AUTH_HEADER]	"header",
	[BACKEND_AUTH_X509]		"x509",
	[BACKEND_AUTH_POSTMAN]	"postman",
};

const char *backend_format_labels[] = {
	[BACKEND_FORMAT_SENML]		"senml",
	[BACKEND_FORMAT_POSTMAN]	"postman",
	[BACKEND_FORMAT_TEMPLATE]	"template",
	[BACKEND_FORMAT_BINARY]		"binary",
};

const char *metric_labels[] = {
	[METRIC_Temperature] 			"Temperature",
	[METRIC_Humidity]				"Humidity",
	[METRIC_Pressure]				"Pressure",
	[METRIC_CO2]					"CO2",
	[METRIC_PM1]					"PM1",
	[METRIC_PM2o5]					"PM2o5",	///
	[METRIC_PM4]					"PM4",
	[METRIC_PM10]					"PM10",
	[METRIC_VOC]					"VOC",
	[METRIC_NOx]					"NOx",
	[METRIC_ProbeTemperature] 		"ProbeTemperature",
	[METRIC_InfraredTemperature]	"InfraredTemperature",
	[METRIC_InternalTemperature]	"InternalTemperature",
	[METRIC_LightIntensity]			"LightIntensity",
	[METRIC_UpTime]					"UpTime",
	[METRIC_FreeHeap]				"FreeHeap",
	[METRIC_AccelerationX]			"AccelerationX",
	[METRIC_AccelerationY]			"AccelerationY",
	[METRIC_AccelerationZ]			"AccelerationZ",
	[METRIC_BatteryLevel]			"BatteryLevel",
	[METRIC_TxPower]				"TransmissionPower",
	[METRIC_Movements]				"Movements",
	[METRIC_RSSI]					"RSSI",
	[METRIC_DCvoltage]				"DCvoltage",
	[METRIC_ADCvalue]				"ADCvalue",
	[METRIC_ProcessorTemperature]	"ProcessorTemperature",
};

const char *unit_labels[] = {
	[UNIT_NONE] 	"",
	[UNIT_Cel] 		"Cel",
	[UNIT_RH]		"%RH",
	[UNIT_hPa]		"hPa",
	[UNIT_ppm]		"ppm",
	[UNIT_ug_m3]	"ug/m3",
	[UNIT_lux]		"lux",
	[UNIT_m_s2]		"m/s2",
	[UNIT_V]		"V",
	[UNIT_dBm]		"dBm",
	[UNIT_ratio]	"/",
	[UNIT_s]		"s",
	[UNIT_B]		"B",
};

const char *wifi_status_labels[] = {
	[WIFI_STATUS_DISCONNECTED]	"disconnected",
	[WIFI_STATUS_ERROR]			"error",
	[WIFI_STATUS_CONNECTED]		"connected",
	[WIFI_STATUS_ONLINE]		"online",
};


uint32_t enums_resource_handler(uint32_t method, bp_pack_t *reader, bp_pack_t *writer)
{
    bool ok = true;

    if(method == PM_GET) {
        ok = ok && bp_create_container(writer, BP_MAP);

	        ok = ok && bp_put_string(writer, "board.model");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 0; i < BOARD_MODEL_NUM_MAX; i++)
		        ok = ok && bp_put_string(writer, board_model_labels[i]);
	        ok = ok && bp_finish_container(writer);

	        ok = ok && bp_put_string(writer, "backend.auth");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 0; i < BACKEND_AUTH_NUM_MAX; i++)
		        ok = ok && bp_put_string(writer, backend_auth_labels[i]);
	        ok = ok && bp_finish_container(writer);

	        ok = ok && bp_put_string(writer, "backend.format");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 0; i < BACKEND_FORMAT_NUM_MAX; i++)
		        ok = ok && bp_put_string(writer, backend_format_labels[i]);
	        ok = ok && bp_finish_container(writer);

	        ok = ok && bp_put_string(writer, "measurement.resource");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 0; i < RESOURCE_NUM_MAX; i++)
		        ok = ok && bp_put_string(writer, resource_labels[i]);
	        ok = ok && bp_finish_container(writer);

	        ok = ok && bp_put_string(writer, "parts");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 1; i < PART_NUM_MAX; i++) {
		        ok = ok && bp_create_container(writer, BP_LIST);
		        ok = ok && bp_put_string(writer, parts[i].label);
		        ok = ok && bp_put_string(writer, resource_labels[parts[i].resource]);
		        ok = ok && bp_put_integer(writer, parts[i].id_start);
		        ok = ok && bp_put_integer(writer, parts[i].id_span);
		        ok = ok && bp_finish_container(writer);
	        }
	        ok = ok && bp_finish_container(writer);

	        ok = ok && bp_put_string(writer, "wifi.status");
	        ok = ok && bp_create_container(writer, BP_LIST);
	        for(int i = 0; i < WIFI_STATUS_NUM_MAX; i++)
		        ok = ok && bp_put_string(writer, wifi_status_labels[i]);
	        ok = ok && bp_finish_container(writer);

        ok = ok && bp_finish_container(writer);
        return ok ? PM_205_Content : PM_500_Internal_Server_Error;
    }
    else
        return PM_405_Method_Not_Allowed;
}

