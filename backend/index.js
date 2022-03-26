import express from "express";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import cors from "cors";

import db from "./config/Database.js";
import router from "./routes/index.js";

dotenv.config();

const app = express();

// mqtt client and subscribe
client.on("message", async (topic, message) => {
  message = message.toString();
  const ob = JSON.parse(message);
  const temperature = ob.temperature;
  const humidity = ob.humidity;
  const amonia = ob.amonia;

  try {
    await Koya.create({
      temp: temperature,
      hum: humidity,
      amonia: amonia,
      topic: topic,
    });
  } catch (error) {}
});

client.on("connect", () => {
  console.log("Mqtt connected ......");
  client.subscribe(topicSub);
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
