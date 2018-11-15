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

idjit aims pretty low, to be a very quick-n-dirty task tracker. internally,
task/sprint/whatever tracking is modeled as a big dependency graph. it's easy
to take any bigger job and model it as a dependency graph of smaller jobs. and
by giving a job a deadline we can call it a "Sprint", and such a "Sprint" is
dependent on all the jobs within it.

relations between jobs besides "dependency" are expressed by "tags"

