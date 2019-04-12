package idjit

import java.sql.Timestamp
import java.time.Duration
import java.time.Instant
import java.time.temporal.ChronoUnit
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertNotNull

class TaskTest {
    private fun futureTS(days: Long) = Timestamp.from(
        Instant
            .now()
            .truncatedTo(ChronoUnit.DAYS)
            .plus(Duration.ofDays(days))
    )

    @Test
    fun testAppCanCreateTask() {
        val t = Task("Test task", "1w")
        assertNotNull(t, "app can create task")

        assertEquals("1w", t.loe, "Task should have loe")
        assertNotNull(t.eta, "Task should have eta")
        assertEquals(futureTS(7), t.eta, "Task ETA should be calculated")
    }

    @Test
    fun testSimpleDep() {
        val p = Task("Parent", "1w")
        val c = Task("Child", "1w")
        val c2 = Task("Child", "3d")
        p.dep(c)
        p.dep(c2)
        assertEquals(futureTS(14), p.eta, "ETA includes child")
    }

    @Test
    fun testProgress() {
        val t = Task("Test", "35")
        assertFailsWith(IllegalArgumentException::class, "Invalid progress", { t.progress = 105 })
        assertFailsWith(IllegalArgumentException::class, "Invalid progress", { t.progress = -5 })
        t.progress = 29
        assertEquals(29, t.progress, "Setting progress")
    }

    @Test
    fun testProgressEffect() {
        val t = Task("Test", "20d")
        t.progress = 50
        assertEquals(futureTS(10), t.eta, "Setting progress changes eta")
    }

}