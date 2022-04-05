import axios from "axios";
import React, { useEffect, useState } from "react";
import jwtDecode from "jwt-decode";
import { useNavigate } from "react-router-dom";

function Account() {
  const [name, setName] = useState("");
  const [email, setEmail] = useState("");
  const [topic, setTopic] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    refreshToken();
  });

  const refreshToken = async () => {
    try {
      const response = await axios.get("http://localhost:5000/token");
      const decoded = jwtDecode(response.data.accesToken);
      setName(decoded.name);
      setEmail(decoded.email);
      setTopic(decoded.topic);
    } catch (error) {
      if (error.response) {
        navigate("/");
      }
    }
  };
  return (
    <div className="w-max h-max bg-white drop-shadow-lg mt-10 rounded-2xl px-16 pt-8 pb-12">
      <h2 className="text-xl font font-semibold">Profil</h2>

      <div className=" mt-5">
        <div className="flex flex-col md:flex-row">
          <div className="w-24">
            <p className="text-md">Nama </p>
          </div>
          <div className="">
            <p className="text-md font-bold">{name}</p>
          </div>
        </div>

        <div className="flex flex-col md:flex-row">
          <div className="w-24 mt-3">
            <p>Email </p>
          </div>
          <div className="mt-3">
            <p className="text-md font-bold">{email}</p>
          </div>
        </div>

        <div className="flex flex-col md:flex-row">
          <div className="w-24 mt-3">
            <p>Topic setup </p>
          </div>
          <div className="mt-3">
            <p className="text-md font-bold">{topic}</p>
          </div>
        </div>
      </div>
    </div>
  );
}

export default Account;
