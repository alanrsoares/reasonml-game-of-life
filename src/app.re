type state = {grid: Game.grid};

type action =
  | Tick
  | Toggle(Game.position);

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {grid: Game.make_grid(30)},
  reducer: (action, state) =>
    switch action {
    | Tick => ReasonReact.Update({grid: state.grid |> Game.next_generation})
    | Toggle(position) =>
      ReasonReact.Update({grid: state.grid |> Game.toggle(position)})
    },
  render: self =>
    <div>
      <div>
        <Grid
          data=self.state.grid
          onToggle=(
            (y, x) => {
              Js.log("foo");
              self.send(Toggle({y, x}));
            }
          )
        />
      </div>
      <ForkMeOnGithubRibbon />
    </div>
};