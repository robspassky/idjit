package idjit

import java.lang.IllegalArgumentException
import java.sql.Timestamp
import java.time.Duration
import java.time.Instant
import java.time.temporal.ChronoUnit
import java.util.*
import kotlin.math.roundToLong

class Task(val id: String, val desc: String, val loe: String, childrenstr: String) {

    constructor(desc: String, loe: String) : this(UUID.randomUUID().toString(), desc, loe, "")

    var progress: Int = 0

    set(value) {
        if (value > 100 || value < 0) {
            throw IllegalArgumentException("Progress is a percentage from 0-100")
        }
        field = value
    }

    val eta: Timestamp
        get() = Timestamp.from((
            children
                .map{ All.getValue(it).eta }
                .max()
                ?.toInstant()
                ?: Instant
                    .now()
                    .truncatedTo(ChronoUnit.DAYS)
            ).plus(daysLeft())
        )

    val children = mutableSetOf<String>()

    init {
        if (childrenstr.isNotEmpty()) {
            children.addAll(childrenstr.split(',').toSet())
        }
    }

    fun dep(child: Task) = children.add(child.id)

    private fun daysLeft() = Duration.ofDays(
        (parseLoe(loe) * 1.0 * (100.0 - progress) / 100.0).roundToLong()
    )

    init {
        Task.All.put(id, this)
    }

    companion object {
        val All = mutableMapOf<String, Task>()
    }

}