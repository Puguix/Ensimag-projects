import React from "react";
import { Navigate, Outlet } from "react-router-dom";
import { useAuth } from "./Context/AuthContext";

const PrivateRoute = () => {
  const auth = useAuth();
  if (auth.token) {
    return <Outlet />;};
  return <Navigate to="/login" />
};

export default PrivateRoute;