import React, { useState, useEffect } from "react";
import axios from "axios";
import jwtDecode from "jwt-decode";
import { useNavigate } from "react-router-dom";

function Home() {
  const [temp, setTemp] = useState(0);
  const [hum, setHum] = useState(0);
  const [amonia, setAmonia] = useState(0);
  const [lamp, setLamp] = useState("_");
  const [fan, setFan] = useState("_");
  const [fogger, setFogger] = useState("_");
  const [token, setToken] = useState("");
  const [expire, setExpire] = useState("");
  const navigate = useNavigate();
  let id_user;

  useEffect(() => {
    refreshToken();
  }, []);

  useEffect(() => {
    const interval = setInterval(() => {
      const data = id_user;
      const getDataSen = async () => {
        // const userId = await data;
        const result = await axios.get("http://localhost:5000/datasen", {
          params: {
            id: data,
          },
        });
        const koyaData = result.data[0];
        setTemp(koyaData.temp.toFixed(2));
        setHum(koyaData.hum.toFixed(2));
        setAmonia(koyaData.amonia.toFixed(2));
      };
      const getDataAct = async () => {
        // const userId = await data;
        const result = await axios.get("http://localhost:5000/dataact", {
          params: {
            id: data,
          },
        });
        // console.log(result.data[0]);
        const koyaData = result.data[0];
        const lampData = koyaData.lamp;
        const fanData = koyaData.fan;
        const foggerData = koyaData.fogger;

        if (lampData < 40) {
          setLamp("Redup");
        } else if (lampData <= 60) {
          setLamp("sedang");
        } else if (lampData > 60) {
          setLamp("terang");
        }

        if (fanData === 1) {
          setFan("Nyala");
        } else {
          setFan("Padam");
        }

        if (foggerData === 1) {
          setFogger("Nyala");
        } else {
          setFogger("Padam");
        }
      };
      getDataSen();
      getDataAct();
    }, 500);
    return () => {
      clearInterval(interval);
    };
  }, []);

  const refreshToken = async () => {
    try {
      const response = await axios.get("http://localhost:5000/token");
      const decoded = jwtDecode(response.data.accesToken);
      return (id_user = decoded.userId);
    } catch (error) {
      if (error.response) {
        navigate("/");
      }
    }
  };

  // const axiosJwt = axios.create();

  // axiosJwt.interceptors.request.use(
  //   async (config) => {
  //     const currentDate = new Date();
  //     if (expire * 1000 < currentDate.getTime()) {
  //       const response = await axios.get("http://localhost:5000/token");
  //       config.headers.Authorization = `Bearer ${response.data.accesToken}`;
  //       setToken(response.data.accesToken);
  //       const decoded = jwtDecode(response.data.accesToken);
  //       setExpire(decoded.exp);
  //     }
  //     return config;
  //   },
  //   (error) => {
  //     return Promise.reject(error);
  //   }
  // );

  // const getUsers = async () => {
  //   const response = await axiosJwt
  //     .get("http://localhost:5000/users", {
  //       headers: {
  //         Authorization: `Bearer ${token}`,
  //       },
  //     })
  //     .then((result) => result);

  //   return response.data[0].id;
  // };

  return (
    <>
      <h2 className="w-max mx-auto mt-5 px-10 py-4 rounded-xl  text-xl font-bold bg-gradient-to-r from-blue-500 to-blue-600 text-white text-center">
        Aplikasi Monitoring <br /> Kandang Ayam
      </h2>

      <div className="mt-10 flex flex-wrap justify-center gap-5">
        <div className="card bg-gradient-to-r from-green-400 to-emerald-500 text-white rounded-lg drop-shadow-md px-5 pt-5 pb-14 w-52 h-[200px] ">
          <h2 className="text-xl font-bold mt-5">Suhu</h2>
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
          <h2 className="text-xl font-bold mt-5">Kelembaban</h2>
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
          <h2 className="text-xl font-bold mt-5">Kadar Amoniak</h2>
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

      <div className="mx-5 mt-14 flex flex-wrap justify-center gap-5">
        <div className="bg-gradient-to-r from-orange-400 to-orange-600 text-white rounded-lg drop-shadow-md w-52 h-[200px] ">
          <h2 className="text-xl font-bold ml-5 mt-5">Lampu</h2>
          <div className="flex w-max h-full ml-4 pb-20 justify-center items-center">
            <div className="w-max flex items-center">
              <img src="/asset/lamp.svg" alt="temp." />
            </div>
            <div className="w-full text-center">
              <span className="font-bold text-4xl">{lamp}</span>
            </div>
          </div>
        </div>

        <div className="bg-gradient-to-r from-lime-500 to-lime-700 text-white rounded-lg drop-shadow-md w-52 h-[200px] ">
          <h2 className="text-xl font-bold ml-5 mt-5">Kipas</h2>
          <div className="flex w-max h-full ml-4 pb-20 justify-center items-center">
            <div className="w-max flex items-center">
              <img src="/asset/fan.svg" alt="temp." />
            </div>
            <div className="w-full text-center">
              <span className="font-bold text-4xl">{fan}</span>
            </div>
          </div>
        </div>

        <div className="bg-gradient-to-r from-indigo-400 to-indigo-600 text-white rounded-lg drop-shadow-md w-52 h-[200px] ">
          <h2 className="text-xl font-bold ml-5 mt-5">Fogger</h2>
          <div className="flex w-max h-full ml-4 pb-20 justify-center items-center">
            <div className="w-max flex items-center">
              <img src="/asset/mist.svg" alt="temp." />
            </div>
            <div className="w-full text-center">
              <span className="font-bold text-4xl">{fogger}</span>
            </div>
          </div>
        </div>
      </div>
    </>
  );
}

export default Home;
