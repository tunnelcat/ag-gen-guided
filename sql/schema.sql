CREATE TABLE factbase (
  id SERIAL PRIMARY KEY,
  hash TEXT
);

CREATE TABLE factbase_item (
  factbase_id INTEGER REFERENCES factbase(id),
  f BIGINT,
  type TEXT,
  PRIMARY KEY (factbase_id, f, type)
);

CREATE TABLE asset (
  id SERIAL PRIMARY KEY,
  name TEXT
);

CREATE TABLE quality (
  asset_id INTEGER REFERENCES asset(id),
  property TEXT,
  op TEXT,
  value TEXT,
  PRIMARY KEY (asset_id, property)
);

CREATE TABLE topology (
  asset_from_id INTEGER REFERENCES asset(id),
  asset_to_id INTEGER REFERENCES asset(id),
  direction TEXT,
  property TEXT,
  op TEXT,
  value TEXT,
  PRIMARY KEY (asset_from_id, asset_to_id, property)
);

CREATE TABLE exploit (
  id SERIAL PRIMARY KEY,
  name TEXT,
  params INTEGER
);

CREATE TABLE exploit_precondition (
  id SERIAL PRIMARY KEY,
  exploit_id INTEGER REFERENCES exploit(id),
  type INTEGER, -- 0 for quality, 1 for topology
  param1 INTEGER,
  param2 INTEGER,
  property TEXT,
  value TEXT,
  op TEXT,
  dir TEXT
);

CREATE TABLE exploit_postcondition (
  id SERIAL PRIMARY KEY,
  exploit_id INTEGER REFERENCES exploit(id),
  type INTEGER, -- 0 for quality, 1 for topology
  param1 INTEGER,
  param2 INTEGER,
  property TEXT,
  value TEXT,
  op TEXT,
  dir TEXT,
  action TEXT
);

CREATE TABLE edge (
  id SERIAL PRIMARY KEY,
  from_node INTEGER REFERENCES factbase(id),
  to_node INTEGER REFERENCES factbase(id),
  exploit_id INTEGER REFERENCES exploit(id)
);

CREATE TABLE edge_asset_binding (
  edge_id INTEGER REFERENCES edge(id),
  exploit_param INTEGER,
  asset_id INTEGER REFERENCES asset(id)
);

CREATE TABLE keyvalue (
  id INTEGER PRIMARY KEY,
  property TEXT
);
