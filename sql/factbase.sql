CREATE FUNCTION new_factbase(myhash TEXT) RETURNS INTEGER AS $$
DECLARE
  myid INTEGER;
BEGIN
  IF NOT EXISTS (SELECT 1 FROM factbase WHERE hash = myhash) THEN
    INSERT INTO factbase VALUES (DEFAULT, myhash) RETURNING id INTO myid;
  ELSE
    SELECT id INTO myid FROM factbase WHERE hash = myhash;
  END IF;

  RETURN myid;
END;
$$ LANGUAGE plpgsql;

CREATE FUNCTION new_edge(from_id INTEGER, to_id INTEGER, exploit INTEGER) RETURNS INTEGER AS $$
DECLARE
  myid INTEGER;
BEGIN
  IF NOT EXISTS (SELECT 1 FROM edge WHERE from_node = from_id AND to_node = to_id AND exploit_id = exploit) THEN
    INSERT INTO edge VALUES (DEFAULT, from_id, to_id, exploit) RETURNING id INTO myid;
  ELSE
    SELECT id INTO myid FROM edge WHERE from_node = from_id AND to_node = to_id AND exploit_id = exploit;
  END IF;

  RETURN myid;
END;
$$ LANGUAGE plpgsql;