type state = {grid: Game.grid};

type action =
  | Tick
  | Random
  | Reset
  | Toggle(Game.position);

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {grid: Game.make_random_grid(30)},
  reducer: (action, state) =>
    switch action {
    | Random => ReasonReact.Update({grid: Game.make_random_grid(30)})
    | Reset => ReasonReact.Update({grid: Game.make_blank_grid(30)})
    | Tick => ReasonReact.Update({grid: Game.next_generation(state.grid)})
    | Toggle(position) =>
      ReasonReact.Update({grid: Game.toggle(position, state.grid)})
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