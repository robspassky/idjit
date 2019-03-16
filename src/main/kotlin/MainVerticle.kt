package idjit

import io.vertx.core.AbstractVerticle
import io.vertx.ext.web.Router

class MainVerticle : AbstractVerticle() {
    override fun start() {
        val router = Router.router(vertx)
        router.get("/").handler { it.response().end("hello") }
        vertx.createHttpServer().requestHandler({ router.accept(it) }).listen(9090)
    }
}