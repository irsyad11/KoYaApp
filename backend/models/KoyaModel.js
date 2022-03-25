import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const Koya = db.define(
  "koya",
  {
    temp: {
      type: DataTypes.FLOAT,
    },
    hum: {
      type: DataTypes.FLOAT,
    },
    amonia: {
      type: DataTypes.FLOAT,
    },
    topic: {
      type: DataTypes.STRING,
    },
  },
  {
    freezeTableName: true,
  }
);

export default Koya;
