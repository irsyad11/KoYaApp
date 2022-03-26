import React, { useState } from "react";
import axios from "axios";
import { useNavigate } from "react-router-dom";

const Login = () => {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [msg, setMsg] = useState("Silahkan Login");
  const navigate = useNavigate();

  const Auth = async (e) => {
    e.preventDefault();
    try {
      await axios.post("http://localhost:5000/login", {
        email,
        password,
      });
      navigate("/dashboard");
    } catch (error) {
      if (error.response) {
        setMsg(error.response.data.msg);
      }
    }
  };

  return (
    <div className="flex justify-center items-center bg-gray-400 w-full h-screen">
      <div className="md:w-[500px] xl:w-3/4 h-max px-10 py-10 bg-white rounded-2xl drop-shadow-lg">
        <div className="w-max mx-auto bg-blue- 300 py-2 px-14 rounded-lg">
          <p className="text-center text-lg capitalize font-semibold">{msg}</p>
        </div>
        <form onSubmit={Auth}>
          <div className="mt-10">
            <label className="ml-2 text-lg font-bold">Email</label>
            <div className="mt-2">
              <input
                type="email"
                name="email"
                id="email"
                className="bg-blue-200 w-full px-2 py-4 rounded-lg focus:outline-none focus:bg-blue-300"
                placeholder="example@example.exe"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
              />
            </div>
          </div>
          <div className="mt-5">
            <label className="ml-2 text-lg font-bold">Kata Sandi</label>
            <div className="mt-2">
              <input
                type="password"
                name="password"
                id="password"
                className="bg-blue-200 w-full px-2 py-4 rounded-lg focus:outline-none focus:bg-blue-300"
                placeholder="***************"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
              />
            </div>
          </div>
          <div className="mt-10 w-max mx-auto">
            <button className="w-full md:w-auto px-14 py-3 bg-blue-500 text-white text-lg font-semibold tracking-wider rounded-xl hover:bg-blue-600">
              Masuk
            </button>
          </div>
        </form>
      </div>
    </div>
  );
};

export default Login;
