import express from "express";
import { getUsers, Register, Login, Logout } from "../controllers/Users.js";
import { verifyToken } from "../middleware/VerifyToken.js";
import { refreshToken } from "../controllers/RefreshToken.js";
import { getDataSen } from "../controllers/KoyaSensor.js";
import { getDataAct } from "../controllers/KoyaAktuator.js";

const router = express.Router();

router.get("/users", verifyToken, getUsers);
router.post("/users", Register);
router.post("/login", Login);
router.get("/token", refreshToken);
router.get("/datasen", getDataSen);
router.get("/dataact", getDataAct);
router.delete("/logout", Logout);

export default router;
