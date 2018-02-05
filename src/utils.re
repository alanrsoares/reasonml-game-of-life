let string = ReasonReact.stringToElement;
let array = ReasonReact.arrayToElement;
let list = xs => xs |> Array.of_list |> array;

let style = ReactDOMRe.Style.make;