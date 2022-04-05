import { Outlet } from "react-router-dom";
import Sidebar from "../components/Sidebar";

const Dashboard = () => {
  return (
    <div className="relative w-full h-full flex  bg-slate-200">
      <Sidebar />
      <div className="z-10 max-w-full pb-10 mx-auto flex flex-col">
        <Outlet />
      </div>
    </div>
  );
};

export default Dashboard;
