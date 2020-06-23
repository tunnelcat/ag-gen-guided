INSERT INTO exploit VALUES
(1,' closeAirSupplyValve', 1),
(2, 'earthquake', 2),
(3, 'backupPowerOn', 3),
(4, 'backupPowerChargeLoss', 3),
(5, 'powerRestored', 3),
(6, 'rechargeBackup', 2),
(7, 'moveControlBladeUp1', 3),
(8, 'moveControlBladeUp2', 3),
(9, 'moveControlBladeDown1', 2),
(10, 'moveControlBladeDown2', 2),
(11, 'changeOperationModeManual', 2),
(12, 'changeOperationModePulse', 2),
(13, 'changeOperationModeRundown', 2),
(14, 'changeOperationModeTest', 3),
(15, 'CAMAlarmDilute', 2),
(16, 'diffuserLeak1', 2),
(17, 'diffuserLeak2', 2),
(18, 'updateAreaMonitoringSystem', 2),
(19, 'areaMonitoringSystemAlarm', 2),
(20, 'pressurizeAirTank', 1),
(21, 'pulseControlRod', 2),
(22, 'pulseControlRodFall1', 2),
(23, 'pulseControlRodFall2', 2),
(24, 'tempScram', 2),
(25, 'seismicScram', 2),
(26, 'highFluxScram', 2),
(27, 'buildingEvacScram', 2),
(28, 'manualBeamRoomScram', 2),
(29, 'manualScram', 2),
(30, 'HVSensorScram', 2),
(31, 'executeScram', 2),
(32, 'dropBlades1', 2),
(33, 'dropBlades2', 2),
(34, 'coolantLossShutdown', 2),
(35, 'coolantTempShutdown', 2),
(36, 'fuelTempShutdown', 2),
(37, 'CAMShutdown', 2),
(38, 'areaMonitoringSystemShutdown', 2),
(39, 'ventilationAirDetectorShutdown', 2),
(40, 'coolantLeakShutdown', 2),
(41, 'sensorPowerLoss', 2),
(42, 'controlRodPowerLoss', 2),
(43, 'miscalibrateTempSensorLow', 1),
(44, 'miscalibrateTempSensorHigh', 1),
(45, 'miscalibrateTempSensorHighPowerBase', 2),
(46, 'incTempReading', 1),
(47, 'incSeismicReading', 1),
(48, 'incPowerReading', 1),
(49, 'incFluxReading', 1),
(50, 'triggerCAMAlarm', 1),
(51, 'triggerN16Alarm', 1),
(52, 'triggerAr41Alarm', 1),
(53, 'decCoolantLevelReading', 1),
(54, 'incCoolantTempReading', 1),
(55, 'lockAirSupplyValve', 1),
(56, 'manipulateRecorder', 1),
(57, 'dosScramSensorTrigger', 2),
(58, 'dosScramSensorUntrigger', 2),
(59, 'triggerManualScram', 1),
(60, 'desyncOperationModeScramPulse', 1),
(61, 'desyncOperationModeScramManual', 1),
(62, 'desyncOperationModeOperatorPulse1', 1),
(63, 'desyncOperationModeOperatorPulse2', 2),
(64, 'desyncOperationModeOperatorManual1', 1),
(65, 'desyncOperationModeOperatorManual2', 2),
(66, 'desyncOperationModeOperatorRundown1', 1),
(67, 'desyncOperationModeOperatorRundown2', 2),
(68, 'desyncOperationModeOperatorTest1', 1),
(69, 'desyncOperationModeOperatorTest2', 2),
(70, 'desyncBladePositionHigh1', 2),
(71, 'desyncBladePositionHigh2', 2),
(72, 'desyncBladePositionLow1', 2),
(73, 'desyncBladePositionLow2', 2),
(74, 'moveBladeUpDesync1', 2),
(75, 'moveBladeUpDesync2', 2),
(76, 'moveBladeDownDesync1', 2),
(77, 'moveBladeDownDesync2', 2),
(78, 'compromiseScram', 1);



INSERT INTO exploit_precodition VALUES
/*CREATE TABLE exploit_precondition (
  id SERIAL PRIMARY KEY,
  exploit_id INTEGER REFERENCES exploit(id),
  type INTEGER, -- 0 for quality, 1 for topology
  param1 INTEGER,
  param2 INTEGER,
  property TEXT,
  value TEXT,
  op TEXT,
  dir TEXT
);*/
/*  (DEFAULT, 1, 0, 1, NULL, 'type', 'router', '=', NULL),*/


(1, 1, 0, 1, NULL, 'platform', 'airCompressor', '=', NULL),
(1, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(1, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(1, 4, 0, 1, NULL, 'ctValve', 'open', '=', NULL),
(1, 5, 0, 1, NULL, 'tankPressure', '20', '>', NULL),

(2, 1, 0, 1, NULL, 'platform', 'physical', '=', NULL),
(2, 2, 0, 1, NULL, 'seismicActivity', '.0061', '<', NULL),
(2, 3, 0, NULL, 1, 'platform', 'seismicSensor', '=', NULL),
(2, 4, 0, NULL, 1, 'status', 'ok', '=', NULL),
(2, 5, 1, 1, 2,  'physical', NULL, NULL, '<->'),

(3, 1, 0, 2, NULL, 'platform', 'backupPower', '=', NULL),
(3, 2. 1, 1, 2, 'power', '114', '<', '->'),
(3, 3, 1, 2, 3, 'power', '114', '<', '->'),
(3, 4, 0, 2, NULL, 'chargeLevel', 0, '>', NULL),
(3, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),

(4, 1, 0, 2, NULL, 'platform', 'backupPower', '=', NULL),
(4, 2, 1, 1, 2, 'power', '114', '<', NULL),
(4, 3, 1, 2, 3, 'power', '114', '>=', NULL),
(4, 4, 0, 2, NULL, 'chargeLevel', '0', '>', NULL),
(4, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),

(5, 1, 0, 2, NULL, 'platform', 'backupPower', '=', NULL),
(5, 2, 1, 1, 2, 'power', '114', '>=', NULL),
(5, 3, 1, 2, 3, 'power', '114', '>=', NULL),
(5, 4, 0, 2, 0, 'status', 'ok', '=', NULL),

(6, 1, 0, 2, NULL, 'platform', 'backupPower', '=', NULL),
(6, 2, 1, 1, 2, 'power', '114', '>=', NULL),
(6, 3, 0, 2, NULL, 'chargeLevel', '1', '<', NULL),
(6, 4, 0, 2, NULL, 'status', 'ok', '=', NULL),

(7, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(7, 2, 0, 2, NULL, 'platform', 'controlBlade', '=', NULL),
(7, 3, 0, 3, NULL, 'platform', 'operatorStation', '=', NULL),
(7, 4, 0, 1, NULL, 'status', 'ok', '=', NULL),
(7, 5, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(7, 6, 0, 1, NULL, 'emagPower', 'on', '=', NULL),
(7, 7, 0, 2, NULL, 'actualPosition', '15', '<', NULL),
(7, 8, 0, 2, NULL, 'motorStatus', 'ok', '=', NULL),
(7, 9, 1, 2, 1, 'subcomponent', NULL, NULL, '->'),
(7, 10, 0, 3, NULL, 'operationMode', 'test', '!=', NULL),
(7, 11, 0, 3, NULL, 'operationMode', 'rundown', '!=', NULL),

(8, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(8, 2, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(8, 3, 0, 3, NULL, 'platform', 'operatorStation', '=', NULL),
(8, 4, 0, 1, NULL, 'status', 'ok', '=', NULL),
(8, 5, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(8, 6, 0, 1, NULL, 'emagPower', 'on', '=', NULL),
(8, 7, 0, 2, NULL, 'actualPosition', '15', '<', NULL),
(8, 8, 0, 2, NULL, 'motorStatus', 'ok', '=', NULL),
(8, 9, 1, 2, 1, 'subcomponent', NULL, NULL, '->'),
(8, 10, 0, 3, NULL, 'operationMode', 'test', '!=', NULL),
(8, 11, 0, 3, NULL, 'operationMode', 'rundown', '!=', NULL),

(9, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(9, 2, 0, 2, NULL, 'platform', 'controlBlade', '=', NULL),
(9, 3, 0, 1, NULL, 'status', 'ok', '=', NULL),
(9, 4, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(9, 5, 0, 1, NULL, 'emagPower', 'on', '=', NULL),
(9, 6, 0, 2, NULL, 'actualPosition', '15', '<', NULL),
(9, 7, 0, 2, NULL, 'motorStatus', 'ok', '=', NULL),

(10, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(10, 2, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(10, 3, 0, 1, NULL, 'status', 'ok', '=', NULL),
(10, 4, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(10, 5, 0, 1, NULL, 'emagPower', 'on', '=', NULL),
(10, 6, 0, 2, NULL, 'actualPosition', '15', '<', NULL),
(10, 7, 0, 2, NULL, 'motorStatus', 'ok', '=', NULL),


(11, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(11, 2, 0, 2, NULL, 'platform', 'operatorStation', '=', NULL),
(11, 3, 0, 1, NULL, 'status', 'ok', '=', NULL),
(11, 4, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(11, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(11, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(11, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(11, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(12, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(12, 2, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(12, 3, 0, 1, NULL, 'status', 'ok', '=', NULL),
(12, 4, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(12, 5, 0, 1, NULL, 'emagPower', 'on', '=', NULL),
(12, 6, 0, 2, NULL, 'actualPosition', '15', '<', NULL),
(12, 7, 0, 2, NULL, 'motorStatus', 'ok', '=', NULL),

(13, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(13, 2, 0, 2, NULL, 'platform', 'operatorStation', '=', NULL),
(13, 3, 0, 1, NULL, 'status', 'ok', '=', NULL),
(13, 4, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(13, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(13, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(13, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(13, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(14, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(14, 2, 0, 2, NULL, 'platform', 'operatorStation', '=', NULL),
(14, 3, 0, 3, NULL, 'platform', 'controlRodController', '=', NULL),
(14, 4, 0, 1, NULL, 'status', 'ok', '=', NULL),
(14, 5, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(14, 6, 0, 1, NULL, 'emagPower', 'off', '=', NULL),
(14, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(14, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),
(14, 9, 1, 2, 3, 'connected_modbus_master', NULL, NULL, '->'),
(14, 10, 1, 3, 2, 'connected_modbus_slave', NULL, NULL, '->'),

(15, 1, 0, 1, NULL, 'platform', 'CAM', '=', NULL),
(15, 2, 0, 2, NULL, 'platform', 'ventilationController', '=', NULL),
(15, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(15, 4, 0, 1, NULL, 'airborneRadiation', 'high','=', NULL),
(15, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(15, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(15, 7, 0, 2, NULL, 'mode', 'dilute', '!=', NULL),
(15, 8, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(15, 9, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(16, 1, 0, 1, NULL, 'platform', 'diffuser', '=', NULL),
(16, 2, 0, 2, NULL, 'platform', 'physical', '=', NULL),
(16, 3, 0, 1, NULL, 'powerStatus', 'off', '=', NULL),
(16, 4, 0, 2, NULL, 'N16_level', '100', '<', NULL),

(17, 1, 0, 1, NULL, 'platform', 'diffuser', '=', NULL),
(17, 2, 0, 2, NULL, 'platform', 'physical', '=', NULL),
(17, 3, 0, 1, NULL, 'status', 'compromised', '=', NULL),
(17, 4, 0, 2, NULL, 'N16_level', '100', '<', NULL),

(18, 1, 0, 1, NULL, 'platform', 'N16Detector', '=', NULL),
(18, 2, 0, 2, NULL, 'platform', 'physical', '=', NULL),
(18, 3, 0, 1, NULL, 'powerStatus', 'ok', '=', NULL),
(18, 4, 0, 1, NULL, 'status', 'ok', '=', NULL),
(18, 5, 0, 1, NULL, 'N16_level', 'airRed.N16_level', '<>', NULL),
(18, 6, 1, 2, 1, 'physical', NULL, NULL, '<->'),

(19, 1, 0, 1, NULL, 'platform', 'N16Detector', '=', NULL),
(19, 2, 0, 2, NULL, 'platform', 'evacuationAlarm', '=', NULL),
(19, 3, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(19, 4, 0, 1, NULL, 'status', 'ok', '=', NULL),
(19, 5, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(19, 6, 0, 1, NULL, 'N16_level', '10', '>', NULL),
(19, 7, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),
(19, 8, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),

(20, 1, 0, 1, NULL, 'platform', 'buildingCompressedAir', '=', NULL),
(20, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(20, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(20, 4, 0, 1, NULL, 'compressor', 'on', '=', NULL),
(20, 5, 0, 1, NULL, 'ctValve', 'open', '=', NULL),
(20, 6, 0, 1, NULL, 'tankPressure', '50', '<', NULL),

(21, 1, 0, 1, NULL, 'platform', 'buildingCompressedAir', '=', NULL),
(21, 2, 0, 1, NULL, 'tankPressure', '5', '<', NULL),
(21, 3, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(21, 4, 1, 1, 2, 'pneumatic_open', NULL, NULL, '->'),

(22, 1, 0, 1, NULL, 'platform', 'buildingCompressedAir', '=', NULL),
(22, 2, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(22, 3, 1, 1, 2, 'pneumatic_closed', NULL, NULL, '->'),

(23, 1, 0, 1, NULL, 'platform', 'buildingCompressedAir', '=', NULL),
(23, 2, 0, 1, NULL, 'tankPressure', '5', '<', NULL),
(23, 3, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(23, 4, 1, 1, 2, 'pneumatic_open', NULL, NULL, '->'),

(24, 1, 0, 1, NULL, 'platform', 'tempSensor', '=', NULL),
(24, 2, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(24, 3, 0, 1, NULL, 'temp', '500', '>', NULL),
(24, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(24, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(24, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(24, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(24, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(25, 1, 0, 1, NULL, 'platform', 'seismicSensor', '=', NULL),
(25, 2, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(25, 3, 0, 1, NULL, 'magnitude', '.0061', '>', NULL),
(25, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(25, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(25, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(25, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(25, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(26, 1, 0, 1, NULL, 'platform', 'fluxMonitor', '=', NULL),
(26, 2, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(26, 3, 0, 1, NULL, 'alarmActivated', 'true', '=', NULL),
(26, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(26, 5, 0, 2, NULL, 'mode', 'pulse', '!=', NULL),
(26, 6, 0, 2, NULL, 'status', 'ok', '=', NULL),
(26, 7, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(26, 8, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(26, 9, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(27, 1, 0, 1, NULL, 'platform', 'evacuationAlarm', '=', NULL),
(27, 2, 0, 1, NULL, 'activated', 'true', '=', NULL),
(27, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(27, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(27, 5, 0, 2, NULL, 'status', 'on', '=', NULL),
(27, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(27, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(27, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(28, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(28, 2, 0, 1, NULL, 'activated', 'true', '=', NULL),
(28, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(28, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(28, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(28, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(28, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(28, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(29, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(29, 2, 0, 1, NULL, 'manualScram', 'true', '=', NULL),
(29, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(29, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(29, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(29, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(29, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(29, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(30, 1, 0, 1, NULL, 'platform', 'HVSensor', '=', NULL),
(30, 2, 0, 1, NULL, 'activated', 'true', '=', NULL),
(30, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(30, 4, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(30, 5, 0, 2, NULL, 'status', 'ok', '=', NULL),
(30, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(30, 7, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(30, 8, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(31, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(31, 2, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(31, 3, 0, 2, NULL, 'status', 'ok', '=', NULL),
(31, 4, 0, 2, NULL, 'activated', 'true', '=', NULL),
(31, 5, 1, 2, 1, 'connected_emag_power', NULL, NULL, '->'),

(32, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(32, 2, 0, 2, NULL, 'platform', 'controlBlade', '=', NULL),
(32, 3, 0, 1, NULL, 'emagPower', 'off', '=', NULL),
(32, 4, 1, 2, 1, 'subcomponent', NULL, NULL, '->'),

(33, 1, 0, 1, NULL, 'platform', 'controlRodController', '=', NULL),
(33, 2, 0, 2, NULL, 'platform', 'pulseControlRod', '=', NULL),
(33, 3, 0, 1, NULL, 'emagPower', 'off', '=', NULL),
(33, 4, 1, 2, 1, 'subcomponent', NULL, NULL, '->'),

(34, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(34, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(34, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(34, 4, 0, 2, NULL, 'platform', 'coolantLevelSensor', '=', NULL),
(34, 5, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(34, 6, 0, 2, NULL, 'level', '-8.0', '<', NULL),
(34, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(34, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(35, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(35, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(35, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(35, 4, 0, 2, NULL, 'platform', 'coolantTempSensor', '=', NULL),
(35, 5, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(35, 6, 0, 2, NULL, 'temp', '400', '>', NULL),
(35, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(35, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(36, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(36, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(36, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(36, 4, 0, 2, NULL, 'platform', 'tempSensor', '=', NULL),
(36, 5, 0, 2, NULL, 'temp', '350', '>', NULL),
(36, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(36, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(36, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(37, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(37, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(37, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(37, 4, 0, 2, NULL, 'platform', 'powerSensor', '=', NULL),
(37, 5, 0, 2, NULL, 'powerLevel', '0.9', '>', NULL),
(37, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(37, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(37, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(38, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(38, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(38, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(38, 4, 0, 2, NULL, 'platform', 'CAM', '=', NULL),
(38, 5, 0, 2, NULL, 'airborneFissionProducts', 'high', '=', NULL),
(38, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(38, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(38, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(39, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(39, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(39, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(39, 4, 0, 2, NULL, 'platform', 'N16_Detector', '=', NULL),
(39, 5, 0, 2, NULL, 'N16_level', '10', '>', NULL),
(39, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(39, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(39, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(40, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(40, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(40, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(40, 4, 0, 2, NULL, 'platform', 'Ar41Detector', '=', NULL),
(40, 5, 0, 2, NULL, 'Ar41_level', '10', '>', NULL),
(40, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(40, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(40, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(41, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(41, 2, 0, 1, NULL, 'status', 'ok', '=', NULL),
(41, 3, 0, 1, NULL, 'powerStatus', 'on', '=', NULL),
(41, 4, 0, 2, NULL, 'platform', 'conductivitySensor', '=', NULL),
(41, 5, 0, 2, NULL, 'leakDetected', 'true', '=', NULL),
(41, 6, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(41, 7, 1, 2, 1, 'connected_modbus_slave', NULL, NULL, '->'),
(41, 8, 1, 1, 2, 'connected_modbus_master', NULL, NULL, '->'),

(42, 1, 1, 1, 2, 'power', '126', '<=', '->'),
(42, 2, 1, 1, 2, 'power', '114', '>=', '->'),
(42, 3, 0, 1, NULL, 'platform', 'physical', '=', NULL),
(42, 4, 0, 1, NULL, 'buildingPower', 'on', '=', NULL),
(42, 5, 0, 2, NULL, 'platform', 'controlRodController', '!=', NULL),
(42, 6, 0, 2, NULL, 'platform', 'operatorStation', '!=', NULL),
(42, 7, 0, 2, NULL, 'platform', 'scramUnit', '!=', NULL),
(42, 8, 0, 2, NULL, 'platform', 'controlSystemRecorder', '!=', NULL),

(43, 1, 1, 1, 2, 'power', '126', '<=', '->'),
(43, 2, 1, 1, 2, 'power', '114', '>=', '->'),
(43, 3, 0, 1, NULL, 'platform', 'physical', '=', NULL),
(43, 4, 0, 1, NULL, 'buildingPower', 'on', '=', NULL),
(43, 5, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),

(44, 1, 0, 1, NULL, 'platform', 'tempSensor', '=', NULL),
(44, 2, 0, 1, NULL, 'calibration', 'normal', '=', NULL),

(45, 1, 0, 1, NULL, 'platform', 'tempSensor', '=', NULL),
(45, 2, 0, 1, NULL, 'calibration', 'normal', '=', NULL),

(46, 1, 0, 1, NULL, 'platform', 'tempSensor', '=', NULL),
(46, 2, 0, 1, NULL, 'calibration', 'normal', '=', NULL),
(46, 3, 0, 2, NULL, 'platform', 'physical', '=', NULL),
(46, 4, 1, 2, 1, 'power', '114', '<', '->'),

(47, 1, 0, 1, NULL, 'platform', 'tempSensor', '=', NULL),
(47, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(48, 1, 0, 1, NULL, 'platform', 'seismicSensor', '=', NULL),
(48, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(49, 1, 0, 1, NULL, 'platform', 'powerSensor', '=', NULL),
(49, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(50, 1, 0, 1, NULL, 'platform', 'fixMonitor', '=', NULL),
(50, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(51, 1, 0, 1, NULL, 'platform', 'CAM', '=', NULL),
(51, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(52, 1, 0, 1, NULL, 'platform', 'N16_Detector', '=', NULL),
(52, 2, 0, 1, NULL, 'calibration', 'normal', '=', NULL),

(53, 1, 0, 1, NULL, 'platform', 'Ar41Detector', '=', NULL),
(53, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(54, 1, 0, 1, NULL, 'platform', 'coolantLevelSensor', '=', NULL),
(54, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(55, 1, 0, 1, NULL, 'platform', 'coolantTempSensor', '=', NULL),
(55, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(56, 1, 0, 1, NULL, 'platform', 'buildingCompressedAir', '=', NULL),
(56, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(57, 1, 0, 1, NULL, 'platform', 'controlSystemRecorder', '=', NULL),
(57, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(58, 1, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(58, 2, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(58, 3, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(59, 1, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(59, 2, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(59, 3, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(60, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(60, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(61, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(61, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(62, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(62, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(63, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(63, 2, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(63, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(63, 4, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(63, 5, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(64, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(64, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(65, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(65, 2, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(65, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(65, 4, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(65, 5, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(66, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(66, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(67, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(67, 2, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(67, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(67, 4, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(67, 5, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(68, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(68, 2, 0, 1, NULL, 'status', 'compromised', '=', NULL),

(69, 1, 0, 1, NULL, 'platform', 'operatorStation', '=', NULL),
(69, 2, 0, 2, NULL, 'platform', 'scramUnit', '=', NULL),
(69, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(69, 4, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(69, 5, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(70, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(70, 2, 0, 1, NULL, 'platform', 'controlBlade', '=', NULL),
(70, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),

(71, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(71, 2, 0, 1, NULL, 'platform', 'pulseControlRod', '=', NULL),
(71, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),

(72, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(72, 2, 0, 1, NULL, 'platform', 'controlBlade', '=', NULL),
(72, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),

(73, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(73, 2, 0, 1, NULL, 'platform', 'pulseControlRod', '=', NULL),
(73, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),

(74, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(74, 2, 0, 1, NULL, 'platform', 'controlBlade', '=', NULL),
(74, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(74, 4, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(74, 5, 0, 2, NULL, 'emagPower', 'on', '=', NULL),
(74, 6, 0, 1, NULL, 'actualPosition', '15', '<', NULL),
(74, 7, 0, 1, NULL, 'motorStatus', 'ok', '=', NULL),

(75, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(75, 2, 0, 1, NULL, 'platform', 'pulseControlRod', '=', NULL),
(75, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(75, 4, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(75, 5, 0, 2, NULL, 'emagPower', 'on', '=', NULL),
(75, 6, 0, 1, NULL, 'actualPosition', '15', '<', NULL),
(75, 7, 0, 1, NULL, 'motorStatus', 'ok', '=', NULL),

(76, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(76, 2, 0, 1, NULL, 'platform', 'controlBlade', '=', NULL),
(76, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(76, 4, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(76, 5, 0, 2, NULL, 'emagPower', 'on', '=', NULL),
(76, 6, 0, 1, NULL, 'actualPosition', '0', '>', NULL),
(76, 7, 0, 1, NULL, 'motorStatus', 'ok', '=', NULL),

(77, 1, 0, 2, NULL, 'platform', 'controlRodController', '=', NULL),
(77, 2, 0, 1, NULL, 'platform', 'pulseControlRod', '=', NULL),
(77, 3, 0, 2, NULL, 'status', 'compromised', '=', NULL),
(77, 4, 0, 2, NULL, 'powerStatus', 'on', '=', NULL),
(77, 5, 0, 2, NULL, 'emagPower', 'on', '=', NULL),
(77, 6, 0, 1, NULL, 'actualPosition', '0', '>', NULL),
(77, 7, 0, 1, NULL, 'motorStatus', 'ok', '=', NULL),

(78, 1, 0, 1, NULL, 'platform', 'scramUnit', '=', NULL),
(78, 2, 0, 1, NULL, 'status', 'ok', '=', NULL);

INSERT INTO exploit_postcondition VALUES
(1, 1, 0, 1, NULL, 'ctValve', 'closed', '=', NULL),

(2, 1, 0, 1, NULL, 'seismicActivity', '.007', '=', NULL),
(2, 2, 0, 2, NULL, 'magnitude', '.007', '=', NULL),

(3, 1, 1, 2, 3, 'power', '120', ':=', '->'),

(4, 1, 0, 2, NULL, 'chargeLevel', '0.05', '-=', NULL),

(5, 1, 1, 2, 3, 'system,power', '0', ':=', '->'),

(6, 1, 0, 2, NULL, 'chargeLevel', '1', ':=', NULL),

(7, 1, 0, 2, NULL, 'actualPosition', '.5', '+=', NULL),
(7, 2, 0, 2, NULL, 'reportedPosition', '.5', '+=', NULL),

(8, 1, 0, 2, NULL, 'actualPosition', '.5', '+=', NULL),
(8, 2, 0, 2, NULL, 'cylinderPosition', '.5', '+=', NULL),
(8, 3, 0, 2, NULL, 'reportedPosition', '.5', '+=', NULL),

(9, 1, 0, 2, NULL, 'actualPosition', '.5', '-=', NULL),
(9, 2, 0, 2, NULL, 'reportedPosition', '.5', '-=', NULL),

(10, 1, 0, 2, NULL, 'actualPosition', '.5', '-=', NULL),
(10, 2, 0, 2, NULL, 'cylinderPosition', '.5', '-=', NULL),
(10, 3, 0, 2, NULL, 'reportedPosition', '.5', '-=', NULL),

(11, 1, 0, 2, NULL, 'operationMode', 'manual', '=', NULL),
(11, 2, 0, 1, NULL, 'mode', 'manual', '=', NULL),

(12, 1, 0, 2, NULL, 'operationMode', 'pulse', '=', NULL),
(12, 2, 0, 1, NULL, 'mode', 'pulse', '=', NULL),

(13, 1, 0, 2, NULL, 'operationMode', 'rundown', '=', NULL),
(13, 2, 0, 1, NULL, 'mode', 'rundown', '=', NULL),

(14, 1, 0, 2, NULL, 'operationMode', 'test', '=', NULL),
(14, 2, 0, 1, NULL, 'mode', 'test', '=', NULL),

(15, 1, 0, 2, NULL, 'mode', 'dilute', '=', NULL),

(16, 1, 0, 2, NULL, 'N16_level', '100', ':=', NULL),

(17, 1, 0, 2, NULL, 'N16_level', '100', ':=', NULL),

(18, 1, 0, 1, NULL, 'N16_level', 'airRed.N16_level', ':=', NULL),

(19, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(20, 1, 0, 1, NULL, 'tankPressure', '5', '=+', NULL),

(21, 1, 0, 2, NULL, 'actualPosition', '15', ':=', NULL),
(21, 2, 0, 2, NULL, 'pulsed', 'true', '=', NULL),
(21, 3, 0, 1, NULL, 'tankPressure', '5', '-=', NULL),

(22, 1, 0, 2, NULL, 'actualPosition', 'pulseRod.cylinderPosition', ':=', NULL),
(22, 2, 0, 2, NULL, 'pulsed', 'false', '=', NULL),

(23, 1, 0, 2, NULL, 'actualPosition', 'pulseRod.cylinderPosition', ':=', NULL),
(23, 2, 0, 2, NULL, 'pulse', 'false', '=', NULL),

(24, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(25, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(26, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(27, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(28, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(29, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(30, 1, 0, 2, NULL, 'activated', 'true', '=', NULL),

(31, 1, 0, 1, NULL, 'emagPower', 'off', '=', NULL),
(31, 2, 1, 2, 1, 'connected_emag_power', NULL, NULL, '->'),

(32, 1, 0, 2, NULL, 'actualPosition', '0', ':=', NULL),

(33, 1, 0, 2, NULL, 'actualPosition', '0', ':=', NULL),

(34, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(35, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(36, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(37, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(38, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(39, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(40, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(41, 1, 0, 1, NULL, 'buildingPower', 'off', '=', NULL),
(41, 2, 0, 2, NULL, 'powerStatus', 'off', '=', NULL),
(41, 3, 1, 1, 2, 'power', '0', ':=', NULL),

(42, 1, 0, 1, NULL, 'buildingPower', 'off', '=', NULL),
(42, 2, 0, 2, NULL, 'powerStatus', 'off', '=', NULL),
(42, 3, 0, 2, NULL, 'emagPower', 'off', '=', NULL),
(42, 4, 1, 1, 2, 'power', '0', ':=', NULL),

(43, 1, 0, 1, NULL, 'calibration', 'low', '=', NULL),
(43, 2, 0, 1, NULL, 'temp', '50', '-=', NULL),

(44, 1, 0, 1, NULL, 'calibration', 'high', '=', NULL),
(44, 2, 0, 1, NULL, 'temp', '50', '+=', NULL),

(45, 1, 0, 1, NULL, 'calibration', 'high', '=', NULL),
(45, 2, 0, 1, NULL, 'temp', '50', '+=', NULL),

(46, 1, 0, 1, NULL, 'temp', '600', ':=', NULL),

(47, 1, 0, 1, NULL, 'magnitude', '.007', ':=', NULL),

(48, 1, 0, 1, NULL, 'powerLevel', '1.5', ':=', NULL),

(49, 1, 0, 1, NULL, 'alarmActivated', 'true', '=', NULL),

(50, 1, 0, 1, NULL, 'airborneRadiation', 'high', '=', NULL),

(51, 1, 0, 1, NULL, 'N16_level', '15', ':=', NULL),

(52, 1, 0, 1, NULL, 'Ar41_level', '15', ':=', NULL),

(53, 1, 0, 1, NULL, 'level', '-10', ':=', NULL),

(54, 1, 0, 1, NULL, 'temp', '600', ':=', NULL),

(55, 1, 0, 1, NULL, 'compressor', 'on', '=', NULL),
(55, 2, 0, 1, NULL, 'ctValve', 'open', '=', NULL),

(56, 1, 0, 1, NULL, 'dataValid', 'false', '=', NULL),

(57, 1, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(57, 2, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),
(57, 3, 0, 2, NULL, 'activated', 'true', '='),

(58, 1, 1, 1, 2, 'connected_modbus_slave', NULL, NULL, '->'),
(58, 2, 1, 2, 1, 'connected_modbus_master', NULL, NULL, '->'),

(59, 1, 0, 1, NULL, 'manualScram', 'true', '=', NULL),

(60, 1, 0, 1, NULL, 'mode', 'pulse', '=', NULL),

(61, 1, 0, 1, NULL, 'mode', 'manual', '=', NULL),

(62, 1, 0, 1, NULL, 'mode', 'pulse', '=', NULL),

(63, 1, 0, 1, NULL, 'mode', 'pulse', '=', NULL),

(64, 1, 0, 1, NULL, 'mode', 'manual', '=', NULL),

(65, 1, 0, 1, NULL, 'mode', 'manual', '=', NULL),

(66, 1, 0, 1, NULL, 'mode', 'rundown', '=', NULL),

(67, 1, 0, 1, NULL, 'mode', 'rundown', '=', NULL),

(68, 1, 0, 1, NULL, 'mode', 'test', '=', NULL),

(69, 1, 0, 1, NULL, 'mode', 'test', '=', NULL),

(70, 1, 0, 1, NULL, 'reportedPosition', '.5', '+=', NULL),

(71, 1, 0, 1, NULL, 'reportedPosition', '.5', '+=', NULL),

(72, 1, 0, 1, NULL, 'reportedPosition', '.5', '-=', NULL),

(73, 1, 0, 1, NULL, 'reportedPosition', '.5', '-=', NULL),

(74, 1, 0, 1, NULL, 'actualPosition', '.5', '+=', NULL),

(75, 1, 0, 1, NULL, 'actualPosition', '.5', '+=', NULL),

(76, 1, 0, 1, NULL, 'actualPosition', '.5', '-=', NULL),

(77, 1, 0, 1, NULL, 'actualPosition', '.5', '-=', NULL),

(78, 1, 0, 1, NULL, 'status', 'compromised', '=', NULL);
