import React, { useState, useEffect } from "react";
import axios from "axios";
import jwtDecode from "jwt-decode";
import { useNavigate } from "react-router-dom";

function Home() {
  const [temp, setTemp] = useState(0);
  const [hum, setHum] = useState(0);
  const [amonia, setAmonia] = useState(0);
  const [token, setToken] = useState("");
  const [expire, setExpire] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    refreshToken();
  }, []);

  useEffect(() => {
    const interval = setInterval(() => {
      const data = getUsers();
      const getData = async () => {
        const topic = await data;
        const result = await axios.get("http://localhost:5000/data", {
          params: {
            topic: topic,
          },
        });
        const koyaData = result.data[0];
        setTemp(koyaData.temp);
        setHum(koyaData.hum);
        setAmonia(koyaData.amonia);
      };
      getData();
    }, 500);
    return () => clearInterval(interval);
  }, []);

  const refreshToken = async () => {
    try {
      const response = await axios.get("http://localhost:5000/token");
      setToken(response.data.accesToken);
      const decoded = jwtDecode(response.data.accesToken);
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
        setExpire(decoded.exp);
      }
      return config;
    },
    (error) => {
      return Promise.reject(error);
    }
  );

  const getUsers = async () => {
    const response = await axiosJwt
      .get("http://localhost:5000/users", {
        headers: {
          Authorization: `Bearer ${token}`,
        },
      })
      .then((result) => result);

    return response.data[0].topic;
  };

  return (
    <>
      <div className=" w-full gap-4 px-5 mt-5">
        <h2 className="w-max mx-auto px-10 py-4 rounded-xl mb-5 text-xl font-bold bg-gradient-to-r from-blue-500 to-blue-600 text-white text-center">
          Kontrol Ayamku App
        </h2>
        <div className="w-full flex flex-wrap justify-center gap-5 mt-10">
          <div className="card bg-gradient-to-r from-green-400 to-emerald-500 text-white rounded-lg drop-shadow-md px-5 pt-5 pb-14 w-52 h-[200px] ">
            <h2 className="text-xl font-bold">Suhu</h2>
            <div className="flex items-center h-max py-6 ">
              <div className="w-max flex items-center">
                <img src="/asset/temp.svg" alt="temp." />
              </div>
              <div className="w-full text-center">
                <span className="font-bold text-4xl">{temp}°</span>
              </div>
            </div>
          </div>

          <div className="card bg-gradient-to-r from-cyan-500 to-blue-500 text-white rounded-lg drop-shadow-md px-5 pt-5 pb-14 w-52 h-[200px] ">
            <h2 className="text-xl font-bold">Kelembaban</h2>
            <div className="flex items-center h-max py-6">
              <div className="w-max flex items-center">
                <img src="/asset/hum.svg" alt="temp." />
              </div>
              <div className="w-full text-center">
                <span className="font-bold text-4xl">{hum}%</span>
              </div>
            </div>
          </div>

          <div className="card bg-gradient-to-r from-yellow-500 to-orange-500 text-white rounded-lg drop-shadow-md px-5 pt-5 pb-14 w-64 h-[200px] ">
            <h2 className="text-xl font-bold">Kadar Amoniak</h2>
            <div className="flex items-center h-max py-6">
              <div className="w-max flex items-center">
                <img src="/asset/amonia.svg" alt="temp." />
              </div>
              <div className="w-full text-center">
                <span className="font-bold text-5xl">
                  {amonia}
                  <sup className="text-xl ml-1">ppm</sup>
                </span>
              </div>
            </div>
          </div>
        </div>
        <div className="w-full flex justify-center h-max">
          {/* <button
            onClick={getUsers}
            className="bg-blue-500 mt-10 px-10 py-2 text-xl text-white hover:bg-blue-600 rounded-xl w-max mx-auto"
          >
            test get users
          </button> */}
        </div>
      </div>
    </>
  );
}

export default Home;
