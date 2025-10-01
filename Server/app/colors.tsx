import { Button } from "@nextui-org/button";
import { Switch } from "@nextui-org/switch";
import { useEffect, useState } from "react";
import { HexColorPicker } from "react-colorful";

function useDebounce(cb: string, delay: number) {
    const [debounceValue, setDebounceValue] = useState(cb);
    useEffect(() => {
        const handler = setTimeout(() => {
            setDebounceValue(cb);
        }, delay);

        return () => {
            clearTimeout(handler);
        };
    }, [cb, delay]);
    return debounceValue;
}


export default function ColorsPanel() {
    const [color, setColor] = useState("#aabbcc");
    const [debounceVal, setDebounceVal] = useState("");

    const debounceTimeout = 200; // 200ms debounce

    const debounceValue = useDebounce(color, debounceTimeout);

    useEffect(() => {
        console.log("Debounced:", color);
        setDebounceVal(color);
        fetch(`/setColor?color=${encodeURIComponent(color)}`, {
            method: "POST",
        });
    }, [debounceValue]);

    function handleColorChange(color: string) {
        setColor(color);
    }

    return <div className="w-full flex flex-col items-center justify-center flex-wrap gap-4">
        <p >{color}</p>
        <HexColorPicker color={color} onChange={handleColorChange} />
    </div>;
}