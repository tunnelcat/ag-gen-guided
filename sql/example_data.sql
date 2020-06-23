INSERT INTO asset VALUES
  (DEFAULT, 'routerA'),
  (DEFAULT, 'routerB'),
  (DEFAULT, 'routerC'),
  (DEFAULT, 'laptopA'),
  (DEFAULT, 'laptopB'),
  (DEFAULT, 'laptopC'),
  (DEFAULT, 'tabletA'),
  (DEFAULT, 'tabletB'),
  (DEFAULT, 'tabletC'),
  (DEFAULT, 'smartphoneA'),
  (DEFAULT, 'smartphoneB'),
  (DEFAULT, 'smartphoneC'),
  (DEFAULT, 'tvA'),
  (DEFAULT, 'tvB'),
  (DEFAULT, 'tvC'),
  (DEFAULT, 'desktopA'),
  (DEFAULT, 'desktopB'),
  (DEFAULT, 'desktopC'),
  (DEFAULT, 'printerA'),
  (DEFAULT, 'printerB'),
  (DEFAULT, 'printerC'),
  (DEFAULT, 'nas'),
  (DEFAULT, 'emailserver'),
  (DEFAULT, 'internet'),

  (DEFAULT, 'test_router'),
  (DEFAULT, 'test_workstation');


INSERT INTO quality VALUES
  (1, 'type', '=', 'router'),
  (1, 'version', '=', '1.6'),
  (2, 'type', '=', 'router'),
  (2, 'version', '=', '1.5'),
  (3, 'type', '=', 'router'),
  (3, 'version', '=', '1.4'),

  (4, 'type', '=', 'laptop'),
  (4, 'os', '=', 'winxp'),
  (4, 'adobereader', '=', '4'),
  (5, 'type', '=', 'laptop'),
  (5, 'os', '=', 'win7'),
  (5, 'adobereader', '=', '5'),
  (6, 'type', '=', 'laptop'),
  (6, 'os', '=', 'win10'),
  (6, 'adobereader', '=', '6'),

  (7, 'type', '=', 'tablet'),
  (7, 'os', '=', 'ios'),
  (8, 'type', '=', 'tablet'),
  (8, 'os', '=', 'android'),
  (9, 'type', '=', 'tablet'),
  (9, 'os', '=', 'kindle'),

  (10, 'type', '=', 'smartphone'),
  (10, 'os', '=', 'ios'),
  (10, 'light', '=', 'off'),
  (11, 'type', '=', 'smartphone'),
  (11, 'os', '=', 'android'),
  (11, 'light', '=', 'off'),
  (12, 'type', '=', 'smartphone'),
  (12, 'os', '=', 'blackberry'),
  (12, 'light', '=', 'off'),

  (13, 'type', '=', 'samsung'),
  (14, 'type', '=', 'visio'),
  (15, 'type', '=', 'sony'),

  (16, 'type', '=', 'desktop'),
  (16, 'os', '=', 'win8'),
  (16, 'photoshop', '=', '5'),
  (17, 'type', '=', 'desktop'),
  (17, 'os', '=', 'macosx'),
  (17, 'photoshop', '=', '5'),
  (18, 'type', '=', 'desktop'),
  (18, 'os', '=', 'win10'),
  (18, 'photoshop', '=', '5'),

  (19, 'type', '=', 'printer'),
  (19, 'model', '=', 'hp123'),
  (20, 'type', '=', 'printer'),
  (20, 'model', '=', 'hp456'),
  (21, 'type', '=', 'printer'),
  (21, 'model', '=', 'hp789'),

  (22, 'type', '=', 'nas'),
  (22, 'os', '=', 'freebsd'),
  (23, 'type', '=', 'emailserver'),
  (23, 'owner', '=', 'hillaryclinton'),
  (23, 'contents', '=', 'topsecrets'),
  (23, 'status', '=', 'compromised'),

  (24, 'type', '=', 'internet');

INSERT INTO topology VALUES
  (1, 2, '->', 'connected', NULL, NULL),
  (2, 3, '->','connected', NULL, NULL),
  (1, 3, '->', 'connected', NULL, NULL),
  (1, 2, '->', 'trusted', NULL, NULL),
  (2, 3, '->', 'trusted', NULL, NULL),
  (1, 3, '->', 'trusted', NULL, NULL),

  (1, 24, '->', 'connected', NULL, NULL),
  (2, 24, '->', 'connected', NULL, NULL),
  (3, 24, '->', 'connected', NULL, NULL),
  (1, 24, '->', 'trusted', NULL, NULL),
  (2, 24, '->', 'trusted', NULL, NULL),
  (3, 24, '->', 'trusted', NULL, NULL),

  (1, 4, '->', 'connected', NULL, NULL),
  (1, 4, '->', 'trusted', NULL, NULL),

  (1, 7, '->', 'connected', NULL, NULL),
  (1, 10, '->', 'connected', NULL, NULL),
  (1, 13, '->', 'connected', NULL, NULL),
  (1, 16, '->', 'connected', NULL, NULL),
  (1, 19, '->', 'connected', NULL, NULL),

  (1, 22, '->', 'connected', NULL, NULL),
  (1, 23, '->', 'connected', NULL, NULL),
  (1, 22, '->', 'trusted', NULL, NULL),
  (1, 23, '->', 'trusted', NULL, NULL),

  (2, 5, '->', 'connected', NULL, NULL),
  (2, 8, '->', 'connected', NULL, NULL),
  (2, 11, '->', 'connected', NULL, NULL),
  (2, 14, '->', 'connected', NULL, NULL),
  (2, 17, '->', 'connected', NULL, NULL),
  (2, 20, '->', 'connected', NULL, NULL),

  (2, 22, '->', 'connected', NULL, NULL),
  (2, 23, '->', 'connected', NULL, NULL),
  (2, 22, '->', 'trusted', NULL, NULL),
  (2, 23, '->', 'trusted', NULL, NULL),

  (3, 6, '->', 'connected', NULL, NULL),
  (3, 9, '->', 'connected', NULL, NULL),
  (3, 12, '->', 'connected', NULL, NULL),
  (3, 15, '->', 'connected', NULL, NULL),
  (3, 18, '->', 'connected', NULL, NULL),
  (3, 21, '->', 'connected', NULL, NULL),

  (3, 22, '->', 'connected', NULL, NULL),
  (3, 23, '->', 'connected', NULL, NULL),
  (3, 22, '->', 'trusted', NULL, NULL),
  (3, 23, '->', 'trusted', NULL, NULL),

  (10, 24, '->', 'connected', NULL, NULL),
  (11, 24, '->', 'connected', NULL, NULL),
  (12, 24, '->', 'connected', NULL, NULL),
  (10, 24, '->', 'trusted', NULL, NULL),
  (11, 24, '->', 'trusted', NULL, NULL),
  (12, 24, '->', 'trusted', NULL, NULL);

INSERT INTO exploit VALUES
  (DEFAULT, 'router_vuln', 1),
  (DEFAULT, 'printer_vuln', 1),
  (DEFAULT, 'adobereader_vuln', 1),
  (DEFAULT, 'photoshop_vuln', 1),
  (DEFAULT, 'kindle_vuln', 1),
  (DEFAULT, 'hacked', 1);

INSERT INTO exploit_precondition VALUES
  (DEFAULT, 1, 0, 1, NULL, 'type', 'router', '=', NULL),
  (DEFAULT, 1, 0, 1, NULL, 'version', '1.6', '=', NULL),

  (DEFAULT, 2, 0, 1, NULL, 'type', 'printer', '=', NULL),
  (DEFAULT, 2, 0, 1, NULL, 'model', 'hp456', '=', NULL),

  (DEFAULT, 3, 0, 1, NULL, 'type', 'laptop', '=', NULL),
  (DEFAULT, 3, 0, 1, NULL, 'os', 'winxp', '=', NULL),
  (DEFAULT, 3, 0, 1, NULL, 'adobereader', '4', '=', NULL),

  (DEFAULT, 4, 0, 1, NULL, 'type', 'desktop', '=', NULL),
  (DEFAULT, 4, 0, 1, NULL, 'os', 'macosx', '=', NULL),
  (DEFAULT, 4, 0, 1, NULL, 'photoshop', '5', '=', NULL),

  (DEFAULT, 5, 0, 1, NULL, 'type', 'tablet', '=', NULL),
  (DEFAULT, 5, 0, 1, NULL, 'os', 'kindle', '=', NULL),

  (DEFAULT, 6, 0, 1, NULL, 'access', 'root', '=', NULL);

INSERT INTO exploit_postcondition VALUES
  (DEFAULT, 1, 0, 1, NULL, 'access', 'root', '=', NULL, 'add'),
  (DEFAULT, 2, 0, 1, NULL, 'access', 'root', '=', NULL, 'add'),
  (DEFAULT, 3, 0, 1, NULL, 'access', 'root', '=', NULL, 'add'),
  (DEFAULT, 4, 0, 1, NULL, 'access', 'root', '=', NULL, 'add'),
  (DEFAULT, 5, 0, 1, NULL, 'access', 'root', '=', NULL, 'add'),
  (DEFAULT, 6, 0, 1, NULL, 'planet', 'hacked', '=', NULL, 'add');
