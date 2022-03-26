import React, { useState, useEffect } from "react";
import axios from "axios";
import jwtDecode from "jwt-decode";
import { useNavigate } from "react-router-dom";

const Dashboard = () => {
  const [name, setName] = useState("");
  const [token, setToken] = useState("");
  const [expire, setExpire] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    refreshToken();
  }, []);

  const refreshToken = async () => {
    try {
      const response = await axios.get("http://localhost:5000/token");
      setToken(response.data.accesToken);
      const decoded = jwtDecode(response.data.accesToken);
      setName(decoded.name);
      setExpire(decoded.exp);
    } catch (error) {
      if (error.response) {
        navigate("/");
      }
    }
  };

  const axiosJwt = axios.create();

  axiosJwt.interceptors.request.use(
    async (config) => {
      const currentDate = new Date();
      if (expire * 1000 < currentDate.getTime()) {
        const response = await axios.get("http://localhost:5000/token");
        config.headers.Authorization = `Bearer ${response.data.accesToken}`;
        setToken(response.data.accesToken);
        const decoded = jwtDecode(response.data.accesToken);
        setName(decoded.name);
        setExpire(decoded.exp);
      }
      return config;
    },
    (error) => {
      return Promise.reject(error);
    }
  );

  const getUsers = async () => {
    const response = await axiosJwt.get("http://localhost:5000/users", {
      headers: {
        Authorization: `Bearer ${token}`,
      },
    });
    console.log(response.data);
  };

  return (
    <div className="container mx-auto">
      <h1 className=" mt-5 font-bold text-2xl">Welcome Back {name}</h1>
      <button
        onClick={getUsers}
        className="px-8 py-3 rounded-lg font-semibold tracking-wider text-white bg-blue-500 hover:bg-blue-600 mt-5"
      >
        get Users
      </button>
    </div>
  );
};

export default Dashboard;
