[@bs.val]
external requestAnimationFrame : (unit => unit) => int =
  "requestAnimationFrame";

[@bs.val] external cancelAnimationFrame : int => unit = "cancelAnimationFrame";

let text = ReasonReact.stringToElement;

let array = ReasonReact.arrayToElement;

let list = xs => xs |> Array.of_list |> array;

let style = ReactDOMRe.Style.make;