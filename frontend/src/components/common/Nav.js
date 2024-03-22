import React, { useState } from "react";
import { DesktopOutlined, FileOutlined, PieChartOutlined, TeamOutlined, UserOutlined } from "@ant-design/icons";
import { Layout, Menu } from "antd";
const { Sider } = Layout;
import { Outlet, Link, useLocation } from "react-router-dom";
function getItem(label, key, icon, children) {
  return {
    key,
    icon,
    children,
    label,
  };
}

const items = [
  getItem(<Link to="/">Option 1</Link>, "1", <PieChartOutlined />),
  getItem(<Link to="/a">Option 2</Link>, "2", <DesktopOutlined />),
  getItem("Option 3", "3", <UserOutlined />),
  getItem("Option 4", "4", <TeamOutlined />),
  getItem("Option 5", "5", <FileOutlined />),
];

const Nav = () => {
  const [collapsed, setCollapsed] = useState(false);
  const selectedKey = useLocation().pathname;

  const currentKey = () => {
    switch (selectedKey) {
      case "/":
        return ["1"];
      case "/a":
        return ["2"];
      default:
        return ["1"];
    }
  };

  return (
    <Layout
      style={{
        minHeight: "100vh",
      }}>
      <Sider collapsible collapsed={collapsed} onCollapse={(value) => setCollapsed(value)}>
        <div className="demo-logo-vertical" />
        <Menu theme="dark" defaultSelectedKeys={["1"]} mode="inline" items={items} selectedKeys={currentKey()} />
      </Sider>
      <Layout>
        <Outlet />
      </Layout>
    </Layout>
  );
};
export default Nav;
