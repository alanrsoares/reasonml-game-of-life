[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (Utils.text(message)) </h2>
      </div>
      <p className="App-intro">
        (Utils.text("To get started, edit"))
        <code> (Utils.text(" src/app.re ")) </code>
        (Utils.text("and save to reload."))
      </p>
    </div>
};