package idjit

import kotlin.test.*

class CliTest {

    @Test
    fun canAddTask() {
        val args = arrayOf("add", "my task name", "3w")
        main(args)
        Db().use {
            assertEquals("my task name", it.listTasks().first().desc, "Add Task")
        }
    }

    @Test
    fun canRemoveIt() {
        val args = arrayOf("rm", "168")
        main(args)

    }


}
