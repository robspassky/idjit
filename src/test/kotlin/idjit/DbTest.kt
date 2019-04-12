package idjit

import java.nio.file.Files
import java.nio.file.Paths
import kotlin.test.*

const val TEST_DB = "test.db"

class DbTest {
    @Test
    fun canCreateDatabase() {
        Db(TEST_DB).use {
            assertTrue(Files.exists(Paths.get("test.db")), "Database was not created")
        }
    }

    @Test
    fun canAddTask() {
        Db(TEST_DB).use {
            val t = Task("Write idjit", "10w")
            assertEquals(1, it.insertTask(t), "Inserting task")
        }
    }

    @Test
    fun canDeleteTask() {
        Db(TEST_DB).use {
            val t = Task("Write idjit", "10w")
            it.insertTask(t)
            assertEquals(1, it.deleteTask(t), "Deleting task")
        }
    }

    @Test
    fun canListTasks() {
        Db(TEST_DB).use {
            val t = Task("Write idjit", "10w")
            val u = Task("Write db", "3w")
            val v = Task("Write os", "1d")
            val w = Task("Take over world", "10y")
            val x = Task("Take over world", "1y")
            v.dep(t)
            v.dep(u)
            it.insertTask(t)
            it.insertTask(u)
            it.insertTask(v)
            it.insertTask(w)
            it.insertTask(x)
            assertEquals(5, it.listTasks().count(), "Listing task")
        }

    }

    @Test
    fun saveTaskPreservesId() {
        Db(TEST_DB).use {
            val t = Task("test", "1w")
            it.insertTask(t)
            val tasklist = it.listTasks()
            assertEquals(t.id, tasklist.first().id, "Id does not match")
        }

    }

    @Test
    fun testSaveDeps() {
        val p = Task("parent", "6d")
        val c = Task("child", "3d")
        val gc = Task("grandchild", "1d")
        p.dep(c)
        c.dep(gc)
        Db(TEST_DB).use {
            it.insertTask(p)
            it.insertTask(c)
            it.insertTask(gc)
            val tasklist = it.listTasks()
            val parent = tasklist.find { it.id == p.id }!!
            assertEquals(1, parent.children.size, "Dependency was saved")
            assertEquals(c.id, parent.children.first(), "Dependency is correct task")
            val child = tasklist.find { it.id == c.id }!!
            assertEquals(1, child.children.size, "Child was saved")
            assertEquals(gc.id, child.children.first(), "Grandchild is correct")
        }

    }

    @AfterTest
    fun removeDb() {
        Files.deleteIfExists(Paths.get(TEST_DB))
    }
}