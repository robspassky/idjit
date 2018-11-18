CREATE TABLE 'jobs' (
  'id'         TEXT,
  'name'       TEXT,
  'criteria'   TEXT,
  'owner'      TEXT,
  'importance' INTEGER,
  'assignee'   TEXT,
  'state'      INTEGER,
  'status'     INTEGER,
  'points'     INTEGER,
  'deadline'   INTEGER,
  CONSTRAINT 'pk' PRIMARY KEY ('id')
);

CREATE TABLE 'tags' (
  'job_id' TEXT,
  'tag'    TEXT,
  CONSTRAINT 'forward' UNIQUE ('job_id', 'tag'),
  CONSTRAINT 'reverse' UNIQUE ('tag', 'job_id')
);

CREATE TABLE deps (
  'job_id' TEXT,
  'dep_id' TEXT,
  CONSTRAINT forward UNIQUE ('job_id', 'dep_id'),
  CONSTRAINT reverse UNIQUE ('dep_id', 'job_id')
);

CREATE TABLE history (
  'id'         TEXT,
  'timestamp'  INTEGER,
  'author'     TEXT,
  'name'       TEXT,
  'criteria'   TEXT,
  'owner'      TEXT,
  'importance' INTEGER,
  'assignee'   TEXT,
  'state'      INTEGER,
  'status'     INTEGER,
  'points'     INTEGER,
  'deadline'   INTEGER,
  CONSTRAINT 'pk' PRIMARY KEY ('id', 'timestamp', 'author')
);
