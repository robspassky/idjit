idjit
=====

idjit dependency job iteration tracker

idjit tracks the status of "jobs" and their dependencies. a job is any kind of
process which has a measurable goal and may be dependent on one or more other
jobs.

a job has:

name -- short job name <= 30 chars
criteria -- acceptance criteria for this job <= 255 chars
owner -- the one person responsible that this job gets done
importance -- low, normal, high, blocker
assignee -- person responsible for guiding job out of its current state
state -- planning, development, testing, deploying, done
status -- not started, in progress, paused, blocked, finished
points -- size estimate of task (use fibonacci or whatever)
deadline -- optional. useful for jobs which represent Sprints
history -- record all updates
dependencies -- jobs which are required by this job
tags -- #HashTags which can be used to associate jobs arbitrarily (incl. show team ownership)

design goals
============

idjit aims pretty low, to be a very quick-n-dirty task tracker. internally,
task/sprint/whatever tracking is modeled as a big dependency graph. it's easy
to take any bigger job and model it as a dependency graph of smaller jobs. and
by giving a job a deadline we can call it a "Sprint", and such a "Sprint" is
dependent on all the jobs within it.

relations between jobs besides "dependency" are expressed by "tags"

architecture
============

idjit strives to be an *extremely* easy-to-install, lightweight solution.
initial thinking is a statically-linked precompiled binary that is an
all-in-one CLI / web server.

idjit is intended for use within a single repository. running "idjit init
<directory>" will create an sqlite database ".idjit" in the target <directory>
which will hold tasks for that repository.

idjit can be used from the command line by individual contributors to record
their progress. it can be run as a server as well, and via browser users can
see overall progress of a job and its dependencies.

future
======

obviously it would be desirable to be able to track work for more than one
repository at a time. need to think of a way to coordinate between multiple
idjit databases.

first, let jobs have uuid's. jobs can be made dependencies of jobs in a
different database, so long as you have the uuid. you also need an URL that
points to the other database.

then an idjit server should be able to navigate to other databases, either
through http URLs / REST, or non-http URLs and maybe assuming the databases
reside on a local drive. ?

todo
====

1. build the single-repository version, one binary version
2. refactor Job as class to possess Db updates, so no one else need include Db.hpp
3. add default Db constructor to open nearest existing .idjit.db in parents

disclaimer
==========

This was coded for fun, not to replace YouTrack or JIRA (though it it does,
that would be fun, too).

commands
========

    $ idjit init <directory>

Initialize an idjit tracking database in the given directory. This basically
creates an sqlite database and runs the initial ddl.

    $ idjit user <username> <email>

Set the user which will be used for work done with this idjit database

    $ idjit new <short job name> [acceptance criteria]

This will create a new job. The only required argument is short job name.
criteria defaults to ""
owner is set to current user (configured above)
importance is set to normal
assignee is set to current user
state is set to planning
status is set to not started
points is unset
deadline is unset
history has a single "created", "date", "creator"
dependencies is empty
tags is empty

A uuid will be generated for the job and returned as the output of this command.

uuid, "job name", state, status

    $ idjit jobs
    $ idjit <uuid> field value

