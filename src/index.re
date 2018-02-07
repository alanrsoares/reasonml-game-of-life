[@bs.module "./registerServiceWorker"] external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(<App tileSize=14 boardSize=30 />, "root");

register_service_worker();
