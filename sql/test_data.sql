INSERT INTO network VALUES
  (DEFAULT, 'home');

INSERT INTO asset VALUES
  (DEFAULT, 'router', (SELECT id FROM network WHERE name = 'home')),
  (DEFAULT, 'laptop', (SELECT id FROM network WHERE name = 'home')),
  (DEFAULT, 'attacker', (SELECT id FROM network WHERE name = 'home'));

INSERT INTO quality VALUES
  (1, 'type', '=', 'router'),
  (1, 'version', '=', '1.6');

INSERT INTO topology VALUES
  (3, 1, '->', 'connected_web', NULL, NULL),
  (2, 1, '->', 'connected', NULL, NULL);

INSERT INTO exploit VALUES
  (DEFAULT, 'router_vuln', 1);

INSERT INTO exploit_precondition VALUES
  (DEFAULT, 1, 0, 1, NULL, 'type', 'router', '=', NULL),
  (DEFAULT, 1, 0, 1, NULL, 'version', '1.6', '=', NULL);

INSERT INTO exploit_postcondition VALUES
  (DEFAULT, 1, 0, 1, NULL, 'access', 'root', '=', NULL),
  (DEFAULT, 1, 0, 1, NULL, 'light', 'on', '=', NULL);
