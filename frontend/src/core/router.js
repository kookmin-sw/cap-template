import { BrowserRouter, Routes, Route } from "react-router-dom";
import Nav from "../components/common/Nav";

function Router() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Nav />} />
      </Routes>
    </BrowserRouter>
  );
}
export default Router;
