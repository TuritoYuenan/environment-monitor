import { test, expect } from "vitest";
import { windAngleToDirection } from "./fields";

test("maps 0 degree to north", () => {
	expect(windAngleToDirection(0)).toBe("N")
})

test("maps 45 degree to north-east", () => {
	expect(windAngleToDirection(45)).toBe("NE")
})

test("maps 90 degree to east", () => {
	expect(windAngleToDirection(90)).toBe("E")
})

test("maps 135 degree to south-east", () => {
	expect(windAngleToDirection(135)).toBe("SE")
})

test("maps 180 degree to south", () => {
	expect(windAngleToDirection(180)).toBe("S")
})

test("maps 225 degree to south-west", () => {
	expect(windAngleToDirection(225)).toBe("SW")
})

test("maps 270 degree to west", () => {
	expect(windAngleToDirection(270)).toBe("W")
})

test("maps 315 degree to north-west", () => {
	expect(windAngleToDirection(315)).toBe("NW")
})
