import React, { useState } from "react";
import axios from "axios";
import { useNavigate } from "react-router-dom";
import { Link } from "react-router-dom";
import * as FaIcons from "react-icons/fa";
import * as MdIcons from "react-icons/md";

const Sidebar = () => {
  const [isOpen, setIsOpen] = useState(false);
  const navigate = useNavigate();

  function ActHandler() {
    setIsOpen(!isOpen);
  }

  const Logout = async () => {
    try {
      await axios.delete("http://localhost:5000/logout");
      navigate("/");
    } catch (error) {
      console.log(error);
    }
  };

  return (
    <>
      <aside
        className={` ${
          isOpen ? "w-[250px] absolute" : "w-max fixed"
        } z-40 sticky top-0 min-h-screen h-full bg-blue-500 px-5 py-3 transition-all  ease-in-out duration-300`}
      >
        <div
          className={`flex items-center mt-5 ${
            isOpen ? "justify-between" : "justify-center"
          }`}
        >
          {isOpen ? (
            <Link to="/#" className="flex items-center text-white text-2xl">
              <FaIcons.FaHive />
              <span className="ml-2">KOYA</span>
            </Link>
          ) : null}
          <button
            className="p-2 bg-blue-300 bg-opacity-50 rounded-md text-white"
            onClick={ActHandler}
          >
            {isOpen ? <FaIcons.FaArrowLeft /> : <FaIcons.FaArrowRight />}
          </button>
        </div>
        <div className="mt-10 bg-white rounded-lg bg-opacity-10 px-2 py-3">
          <ul>
            <li className="py-3 px-2 rounded-lg text-white hover:cursor-pointer hover:bg-white hover:bg-opacity-25">
              <Link to="/dashboard" className="flex items-center ">
                <div className="text-white">
                  <FaIcons.FaHome />
                </div>
                {isOpen ? <span className="ml-3">Beranda</span> : null}
              </Link>
            </li>

            <li className="py-3 px-2 rounded-lg text-white hover:cursor-pointer hover:bg-white hover:bg-opacity-25">
              <Link to="account" className="flex items-center ">
                <div className="text-white">
                  <FaIcons.FaUserCircle />
                </div>
                {isOpen ? <span className="ml-3">Akun</span> : null}
              </Link>
            </li>

            <li className="py-3 px-2 rounded-lg text-white hover:cursor-pointer hover:bg-white hover:bg-opacity-25">
              <button onClick={Logout} className="flex items-center ">
                <div className="text-white">
                  <MdIcons.MdLogout />
                </div>
                {isOpen ? <span className="ml-3">keluar</span> : null}
              </button>
            </li>
          </ul>
        </div>
      </aside>
    </>
  );
};

export default Sidebar;
