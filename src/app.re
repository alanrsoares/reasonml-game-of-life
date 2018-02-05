type state = {grid: Game.grid};

type action =
  | Tick
  | Random
  | Reset
  | Toggle(Game.position);

let get_seed = () => int_of_float(Js.Date.now());

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {grid: Game.make_random_grid(30, get_seed())},
  reducer: (action, state) =>
    switch action {
    | Random =>
      ReasonReact.Update({grid: Game.make_random_grid(30, get_seed())})
    | Reset => ReasonReact.Update({grid: Game.make_blank_grid(30)})
    | Tick => ReasonReact.Update({grid: Game.next_generation(state.grid)})
    | Toggle(position) =>
      ReasonReact.Update({grid: Game.toggle(position, state.grid)})
    },
  render: self =>
    <div>
      <GridControls
        onReset=((_) => self.send(Reset))
        onRandom=((_) => self.send(Random))
        onTick=((_) => self.send(Tick))
      />
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