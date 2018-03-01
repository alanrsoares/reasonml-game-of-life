[@bs.val]
external request_animation_frame : (unit => unit) => int =
  "requestAnimationFrame";

[@bs.val]
external cancel_animation_frame : int => unit = "cancelAnimationFrame";

let render_string = ReasonReact.stringToElement;

let render_array = ReasonReact.arrayToElement;

let render_list = xs => xs |> Array.of_list |> render_array;

let make_style = ReactDOMRe.Style.make;