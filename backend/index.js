import express from "express";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import cors from "cors";
import * as mqtt from "mqtt";

import db from "./config/Database.js";
import router from "./routes/index.js";
import KoyaSensor from "./models/KoyaSensorModel.js";
import KoyaAktuator from "./models/KoyaAktuatorModel.js";

dotenv.config();

const options = {
  host: "test.mosquitto.org",
  port: 1883,
};
const topicSen = "KoYaAppSensor";
const topicAct = "KoYaAppAktuator";
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
});

client.on("connect", () => {
  console.log("Mqtt connected ......");
  client.subscribe(topicSen);
  client.subscribe(topicAct);
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
