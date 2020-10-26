// #include "Pletacka_debug.hpp"


// void Pletacka_debug::init(PletackaConfig config)
// {
//     debugCfg.debug_IP = config.debugIP;
//     debugCfg.debug_port = config.debugPort;
//     debugCfg.data_port = config.dataPort;
//     debugCfg.remoteDebugOn = config.remoteDebugOn;
//     debugCfg.remoteDataOn = config.remoteDataOn;
//     debugCfg.serialDebugOn = config.serialDebugOn;
//     debugCfg.serialDataOn = config.serialDataOn;


//     if(WiFi.getMode() != WIFI_MODE_STA) 
//     {
//         Serial.println("Debug mode does not work with AP, use WiFi mode");
//     }
    
//     debug_ip.fromString(debugCfg.debug_IP); // Convert String IP to IP Class
    
    
//     if(WiFi.status() == WL_CONNECTED)   // WiFi connection is required
//     {
//         Serial.println("Connecting debug to proxy IP:"+debug_ip.toString());
        
        

//         if(debugCfg.remoteDebugOn)
//         {
//             Debug.setTimeout(1);
//             if (!Debug.connect(debug_ip, debugCfg.debug_port)) {
//                 Serial.println("Can not connect to the debug server");
//                 delay(500);
//             }
            
//         }

//         if(debugCfg.remoteDataOn)
//         {
//             Data.setTimeout(1);
//             if (!Data.connect(debug_ip, debugCfg.data_port)) {
//                 Serial.println("Can not connect to the data server");
//                 delay(500);
//             }
//         }
//     }
//     else
//     {
//         Serial.println("ESP is not conested to the WiFi");
//     }
//     // Debug.println("Connected succesfly to DEBUG\n");
//     // Data.println("Connected succesfly to DATA\n");
//     // Serial.println("Connected succesfly to DEBUG and DATA\n");  

// }


// // void Pletacka_debug::send(String message)
// // {

// // }

// // void Pletacka_debug::debug(String message, String prefix)
// // {
// // 	if (debugCfg.remoteDebugOn)
// // 	{
// // 		Debug.print(prefix + message);
// // 	}

// // 	if (debugCfg.serialDebugOn)
// // 	{
// // 		Serial.print(prefix + message);
// // 	}
// // }

// // void Pletacka_debug::debugln(String message, String prefix)
// // {
// // 	if (debugCfg.remoteDebugOn)
// // 	{
// // 		Debug.println(prefix + message);
// // 	}

// // 	if (debugCfg.serialDebugOn)
// // 	{
// // 		Serial.println(prefix + message);
// // 	}
// // }

// // void Pletacka_debug::print(String message, String prefix)
// // {
// // 	if (debugCfg.remoteDataOn)
// // 	{
// // 		Data.print(prefix + message);
// // 	}

// // 	if (debugCfg.serialDebugOn)
// // 	{
// // 		Serial.print(prefix + message);
// // 	}
// // }

// // void Pletacka_debug::println(String message, String prefix)
// // {
// // 	if (debugCfg.remoteDataOn)
// // 	{
// // 		Data.println(prefix + message);
// // 	}

// // 	if (debugCfg.serialDataOn)
// // 	{
// // 		Serial.println(prefix + message);
// // 	}
// // }


