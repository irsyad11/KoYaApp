import express from "express";
import { getUser, Login, Logout, Register } from "../controllers/User.js";
import { refreshToken } from "../controllers/RefreshToken.js";
import { verifyToken } from "../middleware/verifyToken.js";
import { getData } from "../controllers/Koya.js";

const router = express.Router();

router.get("/user", verifyToken, getUser);
router.post("/user", Register);
router.post("/login", Login);
router.get("/token", refreshToken);
router.get("/data", verifyToken, getData);
router.delete("/logout", Logout);

export default router;
