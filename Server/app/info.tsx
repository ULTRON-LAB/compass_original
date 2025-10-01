import { useEffect, useState } from "react";

export default function InfoPanel() {

    const [deviceInfo, setDeviceInfo] = useState({
        buildDate: "",
        buildTime: "",
        buildVersion: "",
        gitBranch: "",
        gitCommit: "",
    });

    useEffect(() => {
        fetch("/info")
            .then(response => response.json())
            .then(data => {
                if (data) {
                    setDeviceInfo(data);
                }
            });
    }, [])

    return <div>
        <ul>
            <li>Version: {deviceInfo.buildVersion}</li>
            <li>Branch: {deviceInfo.gitBranch}</li>
            <li>Commit: {deviceInfo.gitCommit}</li>
            <li>Build Time: {deviceInfo.buildTime}</li>
            <li>Build Date: {deviceInfo.buildDate}</li>
        </ul>
    </div>;
}