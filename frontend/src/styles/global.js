import { createGlobalStyle } from "styled-components";
import { reset } from "styled-reset";

const GlobalStyle = createGlobalStyle`
  ${reset}


  * {
    box-sizing: border-box;
	}

  button:hover {
    cursor: pointer;
  }
`;

export default GlobalStyle;
