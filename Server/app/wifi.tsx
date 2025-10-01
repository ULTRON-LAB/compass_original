'use client';
import { Button } from "@nextui-org/button";
import { Input } from "@nextui-org/input";
import { useEffect, useState } from "react";

export default function WiFiPanel() {
    const [ssid, setSSID] = useState("");
    const [password, setPassword] = useState("");


    useEffect(() => {
        fetch("/wifi")
            .then(response => response.json())
            .then(data => {
                if (data.ssid && data.password) {
                    setSSID(data.ssid);
                    setPassword(data.password);
                }
            });
    }, []);

    function handlePasswordChange(e: any) {
        setPassword(e.target.value);
    }

    function handleSSIDChange(e: any) {
        console.log("SSID changed ", e.target.value);
        setSSID(e.target.value);
    }

    function saveWiFi() {
        fetch(`/setWiFi?ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(password)}`, {
            method: "POST"
        });
    }

    return (
        <div className="flex flex-col items-center justify-center flex-wrap gap-4">
            <p className="px-3 text-start w-full">Save WiFi might cause <br /> the device to restart.<br />And lost the current connection<br />If can not connect to new WiFi<br /> Device will use old WiFi.</p>
            <Input
                type="text"
                label="SSID"
                value={ssid}
                onChange={handleSSIDChange}
            />
            <Input
                type="text"
                label="Password"
                value={password}
                onChange={handlePasswordChange}
            />
            <Button color="primary" variant="ghost" className="max-w-xs" onClick={saveWiFi}>
                Save
            </Button>
        </div>
    );
}