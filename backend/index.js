import express from "express";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import cors from "cors";
import * as mqtt from "mqtt";

import db from "./config/Database.js";
import router from "./routes/index.js";
import KoyaSensor from "./models/KoyaSensorModel.js";
import KoyaAktuator from "./models/KoyaAktuatorModel.js";
import KalmanAmoniaTesting from "./models/Kf1.js";
// import KalmanAmoniaTestingTemp from "./models/Kf2.js";
import KalmanAmoniaTestingHum from "./models/Kf3.js";

dotenv.config();

const options = {
  host: "test.mosquitto.org",
  port: 1883,
};
const topicSen = "KoYaAppSensor";
const topicAct = "KoYaAppAktuator";
const topicKF = "KoyaAppKalmanTest";
const client = mqtt.connect(options);

const app = express();

// mqtt client and subscribe
client.on("message", async (topic, message) => {
  if (topic == topicSen) {
    message = message.toString();
    const ob = JSON.parse(message);
    const temperature = ob.temperature;
    const humidity = ob.humidity;
    const amonia = ob.amonia;
    const id = ob.id;

    try {
      await KoyaSensor.create({
        temp: temperature,
        hum: humidity,
        amonia: amonia,
        id_user: id,
      });
    } catch (error) {}
  }
  if (topic == topicAct) {
    message = message.toString();
    const ob = JSON.parse(message);
    const lamp = ob.lamp;
    const fan = ob.fan;
    const fogger = ob.fogger;
    const id = ob.id;

    try {
      await KoyaAktuator.create({
        lamp: lamp,
        fan: fan,
        fogger: fogger,
        id_user: id,
      });
    } catch (error) {}
  }
  // if (topic == topicKF) {
  //   message = message.toString();
  //   const ob = JSON.parse(message);
  //   const Kd1 = ob.kd1;
  //   const Kd2 = ob.kd2;
  //   const Kd3 = ob.kd3;
  //   const Kd4 = ob.kd4;
  //   const Kd5 = ob.kd5;
  //   const rd = ob.rd;

  //   try {
  //     await KalmanAmoniaTesting.create({
  //       kd1: Kd1,
  //       kd2: Kd2,
  //       kd3: Kd3,
  //       kd4: Kd4,
  //       kd5: Kd5,
  //       rd: rd,
  //     });
  //   } catch (error) {}

  //   // try {
  //   //   await KalmanAmoniaTestingTemp.create({
  //   //     kd1: Kd1,
  //   //     kd2: Kd2,
  //   //     kd3: Kd3,
  //   //     kd4: Kd4,
  //   //     kd5: Kd5,
  //   //     rd: rd,
  //   //   });
  //   // } catch (error) {}

  //   // try {
  //   //   await KalmanAmoniaTestingHum.create({
  //   //     kd1: Kd1,
  //   //     kd2: Kd2,
  //   //     kd3: Kd3,
  //   //     kd4: Kd4,
  //   //     kd5: Kd5,
  //   //     rd: rd,
  //   //   });
  //   // } catch (error) {}
  // }
});

client.on("connect", () => {
  console.log("Mqtt connected ......");
  client.subscribe(topicSen);
  client.subscribe(topicAct);
  client.subscribe(topicKF);
});

client.on("error", () => {
  console.log("error");
});
// end mqtt client

try {
  await db.authenticate();
  console.log("Databse Connected.....");
  await db.sync();
} catch (error) {
  console.log(error);
}

app.use(cors({ credentials: true, origin: "http://localhost:3000" }));
app.use(cookieParser());
app.use(express.json());
app.use(router);

app.listen(5000, () => console.log("server running at port 5000"));
