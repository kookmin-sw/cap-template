import { BrowserRouter, Routes, Route } from "react-router-dom";
import Nav from "../components/common/Nav";
import Test, { Test2 } from "../pages/test";

function Router() {
  return (
    <BrowserRouter>
      <Routes>
        <Route element={<Nav />}>
          <Route path="/" element={<Test />} />
          <Route path="/a" element={<Test2 />} />
        </Route>
      </Routes>
    </BrowserRouter>
  );
}
export default Router;
