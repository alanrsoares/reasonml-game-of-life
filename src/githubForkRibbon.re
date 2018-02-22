let component = ReasonReact.statelessComponent("GithubForkRibbon");

let project_url = "https://github.com/alanrsoares/reasonml-game-of-life";

let ribbon =
  <div className="github-fork-ribbon">
    <a href=project_url> (Utils.render_string("Fork me on Github")) </a>
  </div>;

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <div className="github-fork-ribbon-wrapper right d-none d-md-block"> ribbon </div>
      <div className="github-fork-ribbon-wrapper right-bottom d-block d-md-none"> ribbon </div>
    </div>
};
