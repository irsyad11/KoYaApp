import sequelize from "sequelize";
import db from "../config/Database.js";

const { DataTypes } = sequelize;

const KoyaAktuator = db.define(
  "koya_aktuator",
  {
    lamp: {
      type: DataTypes.FLOAT,
    },
    fan: {
      type: DataTypes.FLOAT,
    },
    fogger: {
      type: DataTypes.FLOAT,
    },
    id_user: {
      type: DataTypes.INTEGER,
    },
  },
  {
    freezeTableName: true,
  }
);

export default KoyaAktuator;
