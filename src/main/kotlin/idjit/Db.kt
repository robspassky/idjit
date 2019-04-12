package idjit

import java.io.Closeable
import java.nio.file.Paths
import java.sql.DriverManager

val TASKS_SQL = mapOf(
    "ddl" to """
         CREATE TABLE IF NOT EXISTS tasks (
            id TEXT PRIMARY KEY,
            description TEXT,
            loe TEXT,
            children TEXT
         );
    """.trimIndent(),
    "insert" to """
        INSERT INTO tasks (
            id,
            description,
            loe,
            children
        ) VALUES (
            ?, ?, ?, ?
        );
    """.trimMargin(),
    "delete" to "DELETE FROM tasks WHERE id = ?",
    "list" to "SELECT * FROM tasks"
)

fun getDefaultDbName(): String =
    Paths.get(System.getenv("HOME")!!, ".idjit", "db").let {
        it.parent.toFile().mkdirs()
        it.toString()
            .also { println(it) }
    }

class Db(name: String) : Closeable {
    constructor() : this(getDefaultDbName())

    val conn = Paths
        .get(name)
        .toString()
        .let {
            DriverManager.getConnection("jdbc:sqlite:$it")
        }
        .also {
            it
                .createStatement()
                .executeUpdate(TASKS_SQL.getValue("ddl"))
        }

    private val insStmt = conn.prepareStatement(TASKS_SQL.getValue("insert"))

    fun insertTask(t: Task) : Int {
        insStmt.setString(1, t.id)
        insStmt.setString(2, t.desc)
        insStmt.setString(3, t.loe)
        insStmt.setString(4, t.children.joinToString())
        return insStmt.executeUpdate()
    }

    private val delStmt = conn.prepareStatement(TASKS_SQL.getValue("delete"))

    fun deleteTask(t: Task): Int {
        delStmt.setString(1, t.id)
        return delStmt.executeUpdate()
    }

    private val listStmt = conn.prepareStatement(TASKS_SQL.getValue("list"))

    fun listTasks() : Sequence<Task> {
        val retval = mutableListOf<Task>()
        listStmt.executeQuery().use {
            while (it.next()) {
                retval.add(
                    Task(
                        it.getString("id"),
                        it.getString("description"),
                        it.getString("loe"),
                        it.getString("children")
                    )
                )
            }
        }
        return retval.asSequence()
    }

    override fun close() {
        conn.close()
    }

}
