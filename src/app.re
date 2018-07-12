open Utils;

[%bs.raw {|require('./app.css')|}];

type state = {
  grid: Game.grid,
  isPlaying: bool,
  animationFrameId: ref(int),
  score: ref(int),
  startedAt: option(float),
  ticks: int,
  frameRate: int,
};

type action =
  | Random
  | Reset
  | Start
  | Stop
  | Tick
  | Toggle(Game.position);

type self_props =
  ReasonReact.self(state, ReasonReact.noRetainedProps, action);

let avg_frame_rate = (ticks, startedAt) =>
  Js.Math.ceil(
    float_of_int(ticks)
    /. ((Js.Date.now() -. startedAt) /. float_of_int(1000)),
  );

let make_seed = () => int_of_float(Js.Date.now());

let component = ReasonReact.reducerComponent("App");

let handle_toggle_autoplay = (_, self: self_props) => {
  let rec play = () => {
    self.state.animationFrameId := request_animation_frame(play);
    self.send(Tick);
  };
  if (self.state.isPlaying) {
    cancel_animation_frame(self.state.animationFrameId^);
    self.send(Stop);
  } else {
    play();
    self.send(Start);
  };
};

let make = (~boardSize, _children) => {
  ...component,
  initialState: () => {
    grid: Game.make_random_grid(boardSize, make_seed()),
    isPlaying: false,
    animationFrameId: ref(0),
    score: ref(0),
    startedAt: None,
    ticks: 0,
    frameRate: 0,
  },
  reducer: (action, state) =>
    switch (action) {
    | Random =>
      ReasonReact.Update({
        ...state,
        grid: Game.make_random_grid(boardSize, make_seed()),
        score: ref(0),
      })
    | Reset =>
      ReasonReact.Update({
        ...state,
        grid: Game.make_blank_grid(30),
        score: ref(0),
        ticks: 0,
      })
    | Start =>
      ReasonReact.Update({
        ...state,
        isPlaying: true,
        startedAt: Some(Js.Date.now()),
      })
    | Stop =>
      ReasonReact.Update({
        ...state,
        isPlaying: false,
        startedAt: None,
        frameRate: 0,
        ticks: 0,
      })
    | Tick =>
      ReasonReact.Update({
        ...state,
        grid: Game.next_generation(state.score, state.grid),
        ticks: state.isPlaying ? state.ticks + 1 : state.ticks,
        frameRate:
          switch (state.startedAt) {
          | None => state.frameRate
          | Some(startedAt) => avg_frame_rate(state.ticks, startedAt)
          },
      })
    | Toggle(position) =>
      ReasonReact.Update({
        ...state,
        grid: Game.toggle_tile(position, state.grid),
      })
    },
  render: self =>
    <div className="App">
      <GridControls
        isPlaying=self.state.isPlaying
        onReset=(_ => self.send(Reset))
        onRandom=(_ => self.send(Random))
        onTick=(_ => self.send(Tick))
        onToggleAutoplay=(self.handle(handle_toggle_autoplay))
      />
      <div className="App--score align-text-center">
        <span className="App--score-label"> (render_string("score")) </span>
        (render_string(string_of_int(self.state.score^)))
      </div>
      <Grid
        data=self.state.grid
        onToggle=((y, x) => self.send(Toggle((y, x))))
      />
      <div className="App--profiler">
        (
          render_string(
            self.state.isPlaying ?
              "avg update rate: "
              ++ string_of_int(self.state.frameRate)
              ++ " fps" :
              "",
          )
        )
      </div>
    </div>,
};